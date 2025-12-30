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
        std::filesystem::path object_directory;
    };

    class Configuration
    {
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

        [[nodiscard]] const std::filesystem::path& projectDirectory() const;
        [[nodiscard]] const std::filesystem::path& buildDirectory() const;
        [[nodiscard]] const std::filesystem::path& binaryDirectory() const;
        [[nodiscard]] const std::filesystem::path& libraryDirectory() const;
        [[nodiscard]] const std::filesystem::path& objectDirectory() const;

        [[nodiscard]] const std::vector<std::string>& flags() const;
        [[nodiscard]] const std::vector<std::string>& defines() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& userIncludes() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& systemIncludes() const;

        bool operator==(const Configuration& other) const = default;
    };
}
