#include "SourceFile.hpp"

namespace cpp_smith
{
    SourceFile::SourceFile(
        const std::filesystem::path& path,
        std::vector<std::filesystem::path> user_deps,
        std::vector<std::filesystem::path> system_deps
    )
        : _path(std::filesystem::absolute(path).lexically_normal())
        , _user_deps(std::move(user_deps))
        , _system_deps(std::move(system_deps))
    {}

    const std::filesystem::path& SourceFile::path() const
    {
        return _path;
    }

    const std::vector<std::filesystem::path>& SourceFile::userDependencies() const
    {
        return _user_deps;
    }

    const std::vector<std::filesystem::path>& SourceFile::systemDependencies() const
    {
        return _system_deps;
    }
}
