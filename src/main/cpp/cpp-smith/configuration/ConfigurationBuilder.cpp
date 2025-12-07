#include "configuration/ConfigurationBuilder.hpp"
#include "Project.hpp"
#include "configuration/Configuration.hpp"

#include "CompilerType.hpp"

namespace cpp_smith
{
    ConfigurationBuilder::ConfigurationBuilder(Project* buildSystem, std::string name)
        : _buildSystem(buildSystem)
        , _name(std::move(name))

        , _compiler(CompilerType::GCC)
    {
    }

    ConfigurationBuilder& ConfigurationBuilder::withCompiler(
        const CompilerType compiler
    )
    {
        _compiler = compiler;
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::withPlatform(
        std::string platform
    )
    {
        _platform = std::move(platform);
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::withArchitecture(
        std::string architecture
    )
    {
        _architecture = std::move(architecture);
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::addFlag(
        std::string flag
    )
    {
        _flags.emplace_back(std::move(flag));
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::addFlags(
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

    ConfigurationBuilder& ConfigurationBuilder::addDefine(
        std::string define
    )
    {
        _defines.emplace_back(std::move(define));
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::addDefines(
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

    ConfigurationBuilder& ConfigurationBuilder::addUserInclude(
        std::filesystem::path dir
    )
    {
        _user_includes.emplace_back(std::move(dir));
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::addUserIncludes(
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

    ConfigurationBuilder& ConfigurationBuilder::addSystemInclude(
        std::filesystem::path dir
    )
    {
        _system_includes.emplace_back(std::move(dir));
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::addSystemIncludes(
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

    Configuration ConfigurationBuilder::create() const
    {
        return {
            _name,
            _compiler,
            _platform,
            _architecture,
            _flags,
            _defines,
            _user_includes,
            _system_includes
        };
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    [[maybe_unused]] Project& ConfigurationBuilder::submit()
    {
        return _buildSystem->accept(create());
    }
}
