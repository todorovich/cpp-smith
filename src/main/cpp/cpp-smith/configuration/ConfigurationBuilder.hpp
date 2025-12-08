#pragma once

#include "Architecture.hpp"
#include "CompilerType.hpp"
#include "Platform.hpp"

#include <filesystem>
#include <string>
#include <vector>

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
        [[maybe_unused]] Project& submit();
    };
}
