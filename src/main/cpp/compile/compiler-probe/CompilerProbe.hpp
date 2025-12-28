#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "../model/Linkable.hpp"

namespace cpp_smith
{
    class CompilationUnit;
    class Configuration;

    class CompilerProbe {
    public:
        virtual ~CompilerProbe() = default;

        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual std::filesystem::path findCompiler() const = 0;
        [[nodiscard]] virtual std::vector<std::filesystem::path> getSystemIncludes() const = 0;
        [[nodiscard]] virtual bool exists() = 0;
        [[nodiscard]] virtual std::string version() = 0;

        [[nodiscard]] virtual std::unique_ptr<Linkable> compile(
            CompilationUnit* compilationUnit,
            const std::filesystem::path& build_directory,
            bool skipRebuildIfUpToDate = true
        ) const = 0;

        virtual void link(
            const std::span<std::unique_ptr<Linkable>>& translation_units,
            const std::filesystem::path& install_directory,
            const std::string& filename
        ) const = 0;

        [[nodiscard]] virtual std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>>
        getDependencies(
            const std::vector<std::string>& compiler_arguments,
            const std::filesystem::path& translation_unit_path
        ) const = 0;
    };
}
