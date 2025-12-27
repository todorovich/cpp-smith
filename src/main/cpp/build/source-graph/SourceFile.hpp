#pragma once

#include "compiler-probe/CompilerProbe.hpp"
#include "compiler-probe/GccProbe.hpp"

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class SourceFile
    {
        const std::filesystem::path _path;
        const std::vector<std::filesystem::path> _direct_dependencies;
        const std::vector<std::filesystem::path> _system_dependencies;

        SourceFile(
            const std::filesystem::path& path,
            std::vector<std::filesystem::path>& _direct_dependencies,
            std::vector<std::filesystem::path>& _system_dependencies
        );

    public:
        static SourceFile from(const std::filesystem::path& path, const CompilerProbe* probe)
        {
            constexpr std::vector<std::string> vector {};

            const auto absolute_path = std::filesystem::absolute(path).lexically_normal();

            auto [direct, system] = probe->getDependencies(vector, absolute_path);

            return SourceFile{ absolute_path, direct, system };
        }

        [[nodiscard]] const std::filesystem::path& path() const;

        [[nodiscard]] const std::vector<std::filesystem::path>& directDependencies() const;

        [[nodiscard]] const std::vector<std::filesystem::path>& systemDependencies() const;
    };
}
