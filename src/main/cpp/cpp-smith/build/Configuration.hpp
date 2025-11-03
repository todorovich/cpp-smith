#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace cpp_smith
{
    class Configuration
    {
        const std::string _name;
        const std::filesystem::path _compiler;
        const std::vector<std::string> _flags;
        const std::vector<std::string> _defines;
        const std::vector<std::filesystem::path> _user_includes;
        const std::vector<std::filesystem::path> _system_includes;
        const std::string _platform;
        const std::string _architecture;

    public:
        Configuration(
            std::string name,
            std::filesystem::path compiler, // Which configuration type?
            std::vector<std::string> flags,
            std::vector<std::string> defines,
            std::vector<std::filesystem::path> user_includes,
            std::vector<std::filesystem::path> system_includes,
            std::string platform,
            std::string architecture
        );

        [[nodiscard]] const std::string& name() const;
        [[nodiscard]] const std::string& platform() const;
        [[nodiscard]] const std::string& architecture() const;
        [[nodiscard]] const std::filesystem::path& compiler() const;
        [[nodiscard]] const std::vector<std::string>& flags() const;
        [[nodiscard]] const std::vector<std::string>& defines() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& userIncludes() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& systemIncludes() const;
    };
}
