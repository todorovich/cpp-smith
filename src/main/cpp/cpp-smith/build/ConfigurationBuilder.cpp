#include "ConfigurationBuilder.hpp"
#include "BuildSystem.hpp"

namespace cpp_smith
{
    ConfigurationBuilder::ConfigurationBuilder(
        BuildSystem* parent,
        std::string name
    )
        : _parent(parent)
        , _name(std::move(name))
    {}

    ConfigurationBuilder& ConfigurationBuilder::setCompiler(
        std::filesystem::path compiler
    )
    {
        _compiler = std::move(compiler);
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::setPlatform(
        std::string platform
    )
    {
        _platform = std::move(platform);
        return *this;
    }

    ConfigurationBuilder& ConfigurationBuilder::setArchitecture(
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

    Configuration ConfigurationBuilder::build() const
    {
        return Configuration(
            _name,
            _compiler,
            _flags,
            _defines,
            _user_includes,
            _system_includes,
            _platform,
            _architecture
        );
    }

    BuildSystem& ConfigurationBuilder::buildSystem()
    {
        return _parent->add(build());
    }
}
