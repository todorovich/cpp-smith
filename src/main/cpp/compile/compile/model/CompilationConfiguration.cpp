#include "CompilationConfiguration.hpp"

#include <utility>

namespace cpp_smith
{
    CompilationConfiguration::CompilationConfiguration(
        std::string name,
        const Triplet triplet,
        const ProjectPaths& paths,
        std::vector<std::string> flags,
        std::vector<std::string> defines,
        std::vector<std::filesystem::path> user_includes,
        std::vector<std::filesystem::path> system_includes
    )
        // TODO: failing to provide the right type gives the dumbest error. Make it make sense.
        : Configuration(std::move(name), TypeId::of<CompilationConfiguration>())
        , _compiler(triplet.compiler)
        , _platform(triplet.platform)
        , _architecture(triplet.architecture)
        , _project_directory(paths.project_directory)
        , _build_directory(paths.build_directory)
        , _binary_directory(paths.binary_directory)
        , _library_directory(paths.library_directory)
        , _object_directory(paths.object_directory)
        , _flags(std::move(flags))
        , _defines(std::move(defines))
        , _user_includes(std::move(user_includes))
        , _system_includes(std::move(system_includes))
    {}

    const std::string& CompilationConfiguration::name() const
    {
        return _name;
    }

    Platform CompilationConfiguration::platform() const
    {
        return _platform;
    }

    Architecture CompilationConfiguration::architecture() const
    {
        return _architecture;
    }

    CompilerType CompilationConfiguration::compiler() const
    {
        return _compiler;
    }

    const std::filesystem::path& CompilationConfiguration::projectDirectory() const
    {
        return _project_directory;
    }

    const std::filesystem::path& CompilationConfiguration::buildDirectory() const
    {
        return _build_directory;
    }

    const std::filesystem::path& CompilationConfiguration::binaryDirectory() const
    {
        return _binary_directory;
    }

    const std::filesystem::path& CompilationConfiguration::libraryDirectory() const
    {
        return _library_directory;
    }

    const std::filesystem::path& CompilationConfiguration::objectDirectory() const
    {
        return _object_directory;
    }

    const std::vector<std::string>& CompilationConfiguration::flags() const
    {
        return _flags;
    }

    const std::vector<std::string>& CompilationConfiguration::defines() const
    {
        return _defines;
    }

    const std::vector<std::filesystem::path>& CompilationConfiguration::userIncludes() const
    {
        return _user_includes;
    }

    const std::vector<std::filesystem::path>& CompilationConfiguration::systemIncludes() const
    {
        return _system_includes;
    }
}
