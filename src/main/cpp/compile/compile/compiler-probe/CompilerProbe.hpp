#pragma once

#include <string>
#include <vector>
#include <filesystem>

#include "../model/Linkable.hpp"

namespace cpp_smith
{
    class CompilationUnit;
    class CompilationConfiguration;

    enum class LinkingOutput
    {
        Executable,
        SharedLibrary,
        StaticLibrary
    };

    class CompilerProbe {
    public:
        virtual ~CompilerProbe() = default;

        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual std::filesystem::path findCompiler() const = 0;
        [[nodiscard]] virtual std::vector<std::filesystem::path> getSystemIncludes() const = 0;
        [[nodiscard]] virtual bool exists() = 0;
        [[nodiscard]] virtual std::string version() = 0;

        [[nodiscard]] virtual ObjectFile compile(
            CompilationUnit* compilationUnit,
            const std::filesystem::path& build_directory,
            bool skipRebuildIfUpToDate = true
        ) const = 0;

        virtual void link(
            const std::span<Linkable*>& linkables,
            const std::filesystem::path& install_directory,
            const std::string& filename,
            LinkingOutput linkingOutput
        ) const = 0;

        [[nodiscard]] virtual std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>>
        getDependencies(
            const std::vector<std::string>& compiler_arguments,
            const std::filesystem::path& translation_unit_path
        ) const = 0;
    };
}
