#pragma once

#include "CompilerProbe.hpp"
#include "ProbeUtils.hpp"
#include "log/Logger.hpp"

namespace cpp_smith
{
    class CompilationUnit;
    class Configuration;

    class GccProbe final : public CompilerProbe
    {
        static std::string createExecutableLinkCommand(
            const std::span<Linkable*>& linkables,
            const std::filesystem::path& out_path
        );

        static std::string createSharedLibraryLinkCommand(
           const std::span<Linkable*>& linkables,
           const std::filesystem::path& out_path
       );

        static std::string createStaticLibraryLinkCommand(
           const std::span<Linkable*>& linkables,
           const std::filesystem::path& out_path
        );

    public:
        inline static logging::Logger logger = logging::Logger::defaultLogger("cpp_smith::GccProbe");

        static constexpr std::string_view minimal_version = "14.0.0";

        std::string current_version;

        GccProbe()
        {
            current_version = version();
            if (current_version < minimal_version)
            {
                throw faults::unsupported::CompilerVersion(
                    "GCC version must be 14.0.0 or higher. Current version: " + current_version
                );
            }
        }

        [[nodiscard]] std::string name() const override
        {
            return "gcc";
        }

        [[nodiscard]] std::filesystem::path findCompiler() const override
        {
            return "/usr/bin/g++";
        }

        [[nodiscard]] std::vector<std::filesystem::path> getSystemIncludes() const override
        {
            return ParseSystemIncludeSearchPaths(
                "g++ -std=gnu++23 -E -x c++ /dev/null -v"
            );
        }

        [[nodiscard]] std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>>
        getDependencies(
            const std::vector<std::string>& compiler_arguments,
            const std::filesystem::path& translation_unit_path
        ) const override;

        std::string buildCommandWithIncludes(
            const std::filesystem::path& source,
            const std::filesystem::path& objectFilepath,
            const std::filesystem::path& dependencyFilepath,
            const CompilationUnit* compilationUnit
        ) const;

        [[nodiscard]] bool exists() override;

        [[nodiscard]] std::string version() override;

        ObjectFile compile(
            CompilationUnit* compilationUnit,
            const std::filesystem::path& build_directory,
            bool skipRebuildIfUpToDate = true
        ) const override;
        
        void link(
            const std::span<Linkable*>& linkables,
            const std::filesystem::path& installDirectory,
            const std::string& filename,
            LinkingOutput linkType
        ) const override;
    };
}
