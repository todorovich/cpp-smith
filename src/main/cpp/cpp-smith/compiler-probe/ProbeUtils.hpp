#pragma once
#include "Exceptions.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <regex>
#include <sstream>
#include <memory>
#include <cstdio>

namespace fs = std::filesystem;

struct CommandResult {
    int exit_code;       // raw exit status or decoded
    std::string output;  // stdout + stderr
};

inline CommandResult ExecuteCommand(const std::string& cmd)
{
    using Pipe = std::unique_ptr<FILE, int(*)(FILE*)>;

    Pipe pipe(
        popen((cmd + " 2>&1").c_str(), "r"),
        pclose
    );
    if (!pipe) return { -1, {} };

    char buffer[4096];
    std::string out;
    while (fgets(buffer, sizeof(buffer), pipe.get()))
        out += buffer;

    int status = pclose(pipe.release());   // retrieve raw exit status

    int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

    return { exit_code, out };
}

inline std::string ExecuteCommandAndCaptureOutput(const std::string& command_line)
{
    using Pipe = std::unique_ptr<FILE, int(*)(FILE*)>;
    const Pipe pipe(popen((command_line + " 2>&1").c_str(), "r"), pclose);
    if (!pipe) { return {}; }

    char buffer[4096];
    std::string output;
    while (fgets(buffer, sizeof(buffer), pipe.get())) { output += buffer; }
    return output;
}

inline std::vector<fs::path> ParseSystemIncludeSearchPaths(const std::string& driver_command_for_verbose_includes)
{
    std::vector<fs::path> include_directories;

    if (auto [failed, output] = ExecuteCommand(driver_command_for_verbose_includes); !failed)
    {
        std::istringstream stream(output);
        std::string line;
        auto in_section = false;

        while (std::getline(stream, line))
        {
            if (line.find("#include <...> search starts here:") != std::string::npos)
            {
                in_section = true;
                continue;
            }
            if (line.find("End of search list.") != std::string::npos)
            {
                break;
            }
            if (in_section)
            {
                if (std::string trimmed = std::regex_replace(line, std::regex(R"(^\s+)"), "");

                    !trimmed.empty()
                )
                {
                    include_directories.emplace_back(trimmed);
                }
            }
        }
        return include_directories;
    }
    else
    {
        throw exceptions::ParseSystemIncludesFailed(
            std::format("Command Execution Failed\nCommand: {} ", driver_command_for_verbose_includes)
        );
    }

}

inline std::vector<fs::path> ParseMakeStyleDependencies(const std::string& make_style_dependency_text)
{
    std::string s = make_style_dependency_text;
    s = std::regex_replace(s, std::regex("\\\\\n"), " ");

    const auto colon = s.find(':');
    if (colon == std::string::npos) { return {}; }

    const std::string rhs = s.substr(colon + 1);

    std::vector<fs::path> dependencies;
    std::istringstream is(rhs);
    std::string token;

    while (is >> token)
    {
        if (token == "|" || token == "\\") { continue; }
        dependencies.emplace_back(token);
    }
    return dependencies;
}

inline bool IsPathUnderAnyRootDirectory(const fs::path& candidate_path,
                                        const std::vector<fs::path>& root_directories)
{
    std::error_code ec;
    fs::path absolute_candidate = fs::weakly_canonical(candidate_path, ec);
    if (ec) { absolute_candidate = fs::absolute(candidate_path, ec); }

    for (const auto& root : root_directories)
    {
        fs::path absolute_root = fs::weakly_canonical(root, ec);
        if (ec) { absolute_root = fs::absolute(root, ec); }
        if (absolute_root.empty()) { continue; }

        auto it_r = absolute_root.begin();
        auto it_c = absolute_candidate.begin();
        for ( ; it_r != absolute_root.end() && it_c != absolute_candidate.end(); ++it_r, ++it_c)
        {
            if (*it_r != *it_c) { break; }
        }
        if (it_r == absolute_root.end()) { return true; }
    }
    return false;
}
