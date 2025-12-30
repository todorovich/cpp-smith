#include "SourceFile.hpp"

namespace cpp_smith
{
    SourceFile::SourceFile(
        const std::filesystem::path& path,
        std::vector<std::filesystem::path>& _direct_dependencies,
        std::vector<std::filesystem::path>& _system_dependencies
    )
        : _path(std::filesystem::absolute(path).lexically_normal())
        , _direct_dependencies(std::move(_direct_dependencies))
        , _system_dependencies(std::move(_system_dependencies))
    {}

    const std::filesystem::path& SourceFile::path() const
    {
        return _path;
    }

    const std::vector<std::filesystem::path>& SourceFile::directDependencies() const
    {
        return _direct_dependencies;
    }

    const std::vector<std::filesystem::path>& SourceFile::systemDependencies() const
    {
        return _system_dependencies;
    }
}
