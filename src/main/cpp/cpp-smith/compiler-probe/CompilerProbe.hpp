#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include <regex>

#include <iostream>
#include <sstream>

inline std::vector<std::filesystem::path> parseIncludes(const std::string& command) {
    std::vector<std::filesystem::path> includes;

    using Pipe = std::unique_ptr<FILE, int(*)(FILE*)>;
    Pipe pipe(popen((command + " 2>&1").c_str(), "r"), pclose);

    if (!pipe) {
        return includes;
    }

    char buffer[4096];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        output += buffer;
    }

    std::istringstream stream(output);
    std::string line;
    bool in_section = false;

    while (std::getline(stream, line)) {
        if (line.find("#include <...> search starts here:") != std::string::npos) {
            in_section = true;
            continue;
        }
        if (line.find("End of search list.") != std::string::npos) {
            break;
        }
        if (in_section) {
            std::string trimmed = std::regex_replace(line, std::regex(R"(^\s+)"), "");
            if (!trimmed.empty()) {
                includes.emplace_back(trimmed);
            }
        }
    }

    return includes;
}



class CompilerProbe {
public:
    virtual ~CompilerProbe() = default;

    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::filesystem::path findCompiler() const = 0;
    [[nodiscard]] virtual std::vector<std::filesystem::path> getSystemIncludes() const = 0;
};

class GccProbe : public CompilerProbe {
public:
    [[nodiscard]] std::string name() const override { return "gcc"; }

    [[nodiscard]] std::filesystem::path findCompiler() const override {
        return "/usr/bin/g++";
    }

    [[nodiscard]] std::vector<std::filesystem::path> getSystemIncludes() const override {
        return parseIncludes("g++ -std=c++23 -E -x c++ /dev/null -v");
    }
};

class ClangProbe : public CompilerProbe {
public:
    [[nodiscard]] std::string name() const override { return "clang"; }

    [[nodiscard]] std::filesystem::path findCompiler() const override {
        return "/usr/bin/clang++";
    }

    [[nodiscard]] std::vector<std::filesystem::path> getSystemIncludes() const override {
        return parseIncludes("clang++ -std=c++23 -E -x c++ /dev/null -v");
    }
};

class MsvcProbe : public CompilerProbe {
public:
    [[nodiscard]] std::string name() const override { return "msvc"; }

    [[nodiscard]] std::filesystem::path findCompiler() const override {
        // Simplified: real version should check registry or vswhere
        return "cl";
    }

    [[nodiscard]] std::vector<std::filesystem::path> getSystemIncludes() const override {
        return parseIncludes("cl /nologo /E /std:c++latest /TP dummy.cpp");
    }
};
