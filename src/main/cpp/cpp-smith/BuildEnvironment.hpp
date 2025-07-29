#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <cstdio>

namespace cpp_smith
{
    class BuildEnvironment
    {
        std::filesystem::path _compiler;
        std::vector<std::string> _flags;
        std::vector<std::string> _defines;
        std::vector<std::filesystem::path> _include_dirs;

        [[nodiscard]] std::vector<std::string> _buildCommandArgs(const std::filesystem::path& source_file) const;
        [[nodiscard]] std::string _joinCommandArgs(const std::vector<std::string>& args) const;
        [[nodiscard]] std::vector<std::filesystem::path> _parseMakefileDeps(FILE* pipe) const;

    public:
        BuildEnvironment(
            std::filesystem::path compiler,
            std::vector<std::string> flags = {},
            std::vector<std::string> defines = {},
            std::vector<std::filesystem::path> include_dirs = {}
        );

        [[nodiscard]] const std::filesystem::path& compiler() const;

        [[nodiscard]] std::vector<std::filesystem::path> resolveDependenciesFor(
            const std::filesystem::path& source_file
        ) const;
    };
}
