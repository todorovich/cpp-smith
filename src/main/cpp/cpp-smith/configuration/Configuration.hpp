#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "CompilerType.hpp"

namespace cpp_smith
{
    class Configuration
    {
        const std::string _name;
        const CompilerType _compiler;
        const std::string _platform;
        const std::string _architecture;
        const std::vector<std::string> _flags;
        const std::vector<std::string> _defines;
        const std::vector<std::filesystem::path> _user_includes;
        const std::vector<std::filesystem::path> _system_includes;

    public:
        Configuration(
            std::string name,
            CompilerType compiler, // Which configuration type?
            std::string platform,
            std::string architecture,
            std::vector<std::string> flags,
            std::vector<std::string> defines,
            std::vector<std::filesystem::path> user_includes,
            std::vector<std::filesystem::path> system_includes
        );

        [[nodiscard]] const std::string& name() const;
        [[nodiscard]] const std::string& platform() const;
        [[nodiscard]] const std::string& architecture() const;

        [[nodiscard]] CompilerType compiler() const;
        [[nodiscard]] const std::vector<std::string>& flags() const;
        [[nodiscard]] const std::vector<std::string>& defines() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& userIncludes() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& systemIncludes() const;

        bool operator==(const Configuration& other) const
        {
            return _name == other._name
                && _compiler == other._compiler
                && _platform == other._platform
                && _architecture == other._architecture
                && _flags == other._flags
                && _defines == other._defines
                && _user_includes == other._user_includes
                && _system_includes == other._system_includes;
        }
    };
}
