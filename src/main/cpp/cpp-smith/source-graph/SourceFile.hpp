#pragma once

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class SourceFile
    {
        std::filesystem::path _path;
        std::vector<std::filesystem::path> _user_deps;
        std::vector<std::filesystem::path> _system_deps;

    public:
        explicit SourceFile(const std::filesystem::path& path);

        [[nodiscard]] const std::filesystem::path& path() const;

        void setDependencies(
            std::vector<std::filesystem::path> user_deps,
            std::vector<std::filesystem::path> system_deps
        );

        [[nodiscard]] const std::vector<std::filesystem::path>& userDependencies() const;
        [[nodiscard]] const std::vector<std::filesystem::path>& systemDependencies() const;
    };
}
