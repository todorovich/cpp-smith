#pragma once

#include "BuildSystem.hpp"
#include "Configuration.hpp"

#include <filesystem>
#include <string>
#include <vector>

class Build; // Forward declaration

class ConfigurationBuilder
{
    Build& _parent;
    std::string _name;
    std::filesystem::path _compiler;
    std::vector<std::string> _flags;
    std::vector<std::string> _defines;
    std::vector<std::filesystem::path> _user_includes;
    std::vector<std::filesystem::path> _system_includes;
    std::string _platform;
    std::string _architecture;

public:
    ConfigurationBuilder(BuildSystem& parent, std::string name);

    // Fluent mutation API
    ConfigurationBuilder& setCompiler(std::filesystem::path compiler);
    ConfigurationBuilder& setPlatform(std::string platform);
    ConfigurationBuilder& setArchitecture(std::string architecture);

    ConfigurationBuilder& addFlag(std::string flag);
    ConfigurationBuilder& addFlags(std::vector<std::string> flags);
    ConfigurationBuilder& addDefine(std::string define);
    ConfigurationBuilder& addDefines(std::vector<std::string> defines);
    ConfigurationBuilder& addUserInclude(std::filesystem::path dir);
    ConfigurationBuilder& addUserIncludes(std::vector<std::filesystem::path> dirs);
    ConfigurationBuilder& addSystemInclude(std::filesystem::path dir);
    ConfigurationBuilder& addSystemIncludes(std::vector<std::filesystem::path> dirs);

    // Returns finalized Configuration
    Configuration build() const;

    // Registers into Build and returns Build&
    Build& buildSystem();
};
