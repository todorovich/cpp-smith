#pragma once

#include "Architecture.hpp"

#include <filesystem>
#include <string>
#include <vector>

#include "CompilerType.hpp"
#include "Platform.hpp"

namespace cpp_smith
{
    struct Triplet
    {
        CompilerType compiler;
        Platform platform;
        Architecture architecture;
    };

    struct ProjectPaths
    {
        std::filesystem::path project_directory;
        std::filesystem::path build_directory;
        std::filesystem::path binary_directory;
        std::filesystem::path library_directory;
    };

    class Configuration
    {
        const std::string _name;
        const CompilerType _compiler;
        const Platform _platform;
        const Architecture _architecture;

        const std::filesystem::path _project_directory;
        const std::filesystem::path _build_directory;
        const std::filesystem::path _binary_directory;
        const std::filesystem::path _library_directory;

        const std::vector<std::string> _flags;
        const std::vector<std::string> _defines;
        const std::vector<std::filesystem::path> _user_includes;
        const std::vector<std::filesystem::path> _system_includes;

    public:
        Configuration(
            std::string name,
            Triplet triplet,
            const ProjectPaths& paths,
            std::vector<std::string> flags,
            std::vector<std::string> defines,
            std::vector<std::filesystem::path> user_includes,
            std::vector<std::filesystem::path> system_includes
        );

        [[nodiscard]] const std::string& name() const;

        [[nodiscard]] Platform platform() const;
        [[nodiscard]] Architecture architecture() const;
        [[nodiscard]] CompilerType compiler() const;

        [[nodiscard]] const std::vector<std::string>& flags() const;
        [[nodiscard]] const std::vector<std::string>& defines() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& userIncludes() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& systemIncludes() const;

        bool operator==(const Configuration& other) const = default;
    };
}
