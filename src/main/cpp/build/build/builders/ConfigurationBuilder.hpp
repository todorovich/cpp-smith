#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "compile/model/Architecture.hpp"
#include "compile/model/CompilerType.hpp"
#include "compile/model/Configuration.hpp"
#include "compile/model/Platform.hpp"

namespace cpp_smith
{
    class Project; // Forward declaration
    class Configuration;

    class ConfigurationBuilder
    {
        Project* _buildSystem;
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

    public:
        ConfigurationBuilder(Project* buildSystem, std::string name);

        // Fluent mutation API
        ConfigurationBuilder& withCompiler(CompilerType compiler);
        ConfigurationBuilder& withPlatform(Platform platform);
        ConfigurationBuilder& withArchitecture(Architecture architecture);

        ConfigurationBuilder& withProjectDirectory(const std::filesystem::path& project_directory);
        ConfigurationBuilder& withBuildDirectory(const std::filesystem::path& build_directory);
        ConfigurationBuilder& withBinaryDirectory(const std::filesystem::path& binary_directory);
        ConfigurationBuilder& withLibraryDirectory(const std::filesystem::path& library_directory);
        ConfigurationBuilder& withObjectDirectory(const std::filesystem::path& build_directory);

        ConfigurationBuilder& addFlag(std::string flag);
        ConfigurationBuilder& addFlags(std::vector<std::string> flags);
        ConfigurationBuilder& addDefine(std::string define);
        ConfigurationBuilder& addDefines(std::vector<std::string> defines);
        ConfigurationBuilder& addUserInclude(std::filesystem::path dir);
        ConfigurationBuilder& addUserIncludes(std::vector<std::filesystem::path> dirs);
        ConfigurationBuilder& addSystemInclude(std::filesystem::path dir);
        ConfigurationBuilder& addSystemIncludes(std::vector<std::filesystem::path> dirs);

        // Returns finalized Configuration
        [[nodiscard]] Configuration create() const;

        // Registers into Build and returns Build&
        [[maybe_unused]] const Configuration& submit();
    };
}
