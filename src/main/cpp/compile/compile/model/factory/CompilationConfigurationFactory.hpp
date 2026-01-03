#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "build/Factory.hpp"
#include "build/ProjectInterface.hpp"
#include "compile/model/Architecture.hpp"
#include "compile/model/CompilerType.hpp"
#include "compile/model/CompilationConfiguration.hpp"
#include "compile/model/Platform.hpp"

namespace cpp_smith
{
    class CompilationConfiguration;

    class CompilationConfigurationFactory
    {
        ProjectInterface* _project;
        std::string _name;

        CompilerType _compiler;
        Platform _platform;
        Architecture _architecture;

        std::filesystem::path _project_directory;
        std::filesystem::path _build_directory;
        std::filesystem::path _binary_directory;
        std::filesystem::path _library_directory;
        std::filesystem::path _object_directory;

        std::vector<std::string> _flags;
        std::vector<std::string> _defines;
        std::vector<std::filesystem::path> _user_includes;
        std::vector<std::filesystem::path> _system_includes;

        CompilationConfigurationFactory(ProjectInterface* buildSystem, std::string name);

    public:
        friend struct Factory<CompilationConfiguration>;

        // Fluent mutation API
        CompilationConfigurationFactory& withCompiler(CompilerType compiler);
        CompilationConfigurationFactory& withPlatform(Platform platform);
        CompilationConfigurationFactory& withArchitecture(Architecture architecture);

        CompilationConfigurationFactory& withProjectDirectory(const std::filesystem::path& project_directory);
        CompilationConfigurationFactory& withBuildDirectory(const std::filesystem::path& build_directory);
        CompilationConfigurationFactory& withBinaryDirectory(const std::filesystem::path& binary_directory);
        CompilationConfigurationFactory& withLibraryDirectory(const std::filesystem::path& library_directory);
        CompilationConfigurationFactory& withObjectDirectory(const std::filesystem::path& build_directory);

        // TODO: add with versions to replace all
        CompilationConfigurationFactory& addFlag(std::string flag);
        CompilationConfigurationFactory& addFlags(std::vector<std::string> flags);
        CompilationConfigurationFactory& addDefine(std::string define);
        CompilationConfigurationFactory& addDefines(std::vector<std::string> defines);
        CompilationConfigurationFactory& addUserInclude(std::filesystem::path dir);
        CompilationConfigurationFactory& addUserIncludes(std::vector<std::filesystem::path> dirs);
        CompilationConfigurationFactory& addSystemInclude(std::filesystem::path dir);
        CompilationConfigurationFactory& addSystemIncludes(std::vector<std::filesystem::path> dirs);

        // Returns finalized Configuration
        [[nodiscard]] std::unique_ptr<CompilationConfiguration> create() const;

        // Registers into Build and returns Build&
        [[maybe_unused]] const CompilationConfiguration& submit();
    };

    template <>
    struct Factory<CompilationConfiguration>
    {
        using factory = CompilationConfigurationFactory;

        static factory create(ProjectInterface& project, std::string name)
        {
            auto project_coordinates = project.getProjectCoordinates();

            return factory{ &project, std::move(name) }
                   .withProjectDirectory(project.getProjectDirectory())
                   .withBuildDirectory(
                       std::filesystem::path{"build"}
                       / project_coordinates.group
                       / project_coordinates.project
                       / std::format("{}",project_coordinates.version)
                   )
                   .withBinaryDirectory("bin")
                   .withLibraryDirectory("lib")
                   .withObjectDirectory("obj");;
        }
    };
}
