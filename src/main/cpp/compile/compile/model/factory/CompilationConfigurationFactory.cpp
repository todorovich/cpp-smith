#include "build/ProjectInterface.hpp"
#include "compile/model/CompilationConfiguration.hpp"
#include "compile/model/CompilerType.hpp"
#include "compile/model/factory/CompilationConfigurationFactory.hpp"

namespace cpp_smith
{
    CompilationConfigurationFactory::CompilationConfigurationFactory(ProjectInterface* buildSystem, std::string name)
        : _project(buildSystem)
        , _name(std::move(name))

        , _compiler(CompilerType::GCC)
    {
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withCompiler(
        const CompilerType compiler
    )
    {
        _compiler = compiler;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withPlatform(
        const Platform platform
    )
    {
        _platform = platform;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withArchitecture(
        const Architecture architecture
    )
    {
        _architecture = architecture;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withProjectDirectory(
        const std::filesystem::path& project_directory
    )
    {
        _project_directory = project_directory;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withBuildDirectory(
        const std::filesystem::path& build_directory
    )
    {
        _build_directory = build_directory;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withBinaryDirectory(
        const std::filesystem::path& binary_directory
    )
    {
        _binary_directory = binary_directory;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withLibraryDirectory(
        const std::filesystem::path& library_directory
    )
    {
        _library_directory = library_directory;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::withObjectDirectory(
        const std::filesystem::path& object_directory
    )
    {
        _object_directory = object_directory;
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addFlag(
        std::string flag
    )
    {
        _flags.emplace_back(std::move(flag));
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addFlags(
        std::vector<std::string> flags
    )
    {
        _flags.insert(
            _flags.end(),
            std::make_move_iterator(flags.begin()),
            std::make_move_iterator(flags.end())
        );
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addDefine(
        std::string define
    )
    {
        _defines.emplace_back(std::move(define));
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addDefines(
        std::vector<std::string> defines
    )
    {
        _defines.insert(
            _defines.end(),
            std::make_move_iterator(defines.begin()),
            std::make_move_iterator(defines.end())
        );
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addUserInclude(
        std::filesystem::path dir
    )
    {
        _user_includes.emplace_back(std::move(dir));
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addUserIncludes(
        std::vector<std::filesystem::path> dirs
    )
    {
        _user_includes.insert(
            _user_includes.end(),
            std::make_move_iterator(dirs.begin()),
            std::make_move_iterator(dirs.end())
        );
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addSystemInclude(
        std::filesystem::path dir
    )
    {
        _system_includes.emplace_back(std::move(dir));
        return *this;
    }

    CompilationConfigurationFactory& CompilationConfigurationFactory::addSystemIncludes(
        std::vector<std::filesystem::path> dirs
    )
    {
        _system_includes.insert(
            _system_includes.end(),
            std::make_move_iterator(dirs.begin()),
            std::make_move_iterator(dirs.end())
        );
        return *this;
    }

    std::unique_ptr<CompilationConfiguration> CompilationConfigurationFactory::create() const
    {
        return std::make_unique<CompilationConfiguration>(
            _name,
            Triplet{ _compiler, _platform, _architecture },
            ProjectPaths{
                _project_directory,
                _build_directory,
                _binary_directory,
                _library_directory,
                _object_directory
            },
            _flags,
            _defines,
            _user_includes,
            _system_includes
        );
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    [[maybe_unused]] const CompilationConfiguration& CompilationConfigurationFactory::submit()
    {
        auto configuration = create();

        const auto& compilation_configuration = *configuration.get();

        _project->accept(std::move(configuration));

        return compilation_configuration;
    }
}
