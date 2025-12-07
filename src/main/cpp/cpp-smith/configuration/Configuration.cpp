#include "Configuration.hpp"

#include <utility>

namespace cpp_smith
{
    Configuration::Configuration(
        std::string name,
        const CompilerType compiler,
        std::string platform,
        std::string architecture,
        std::vector<std::string> flags,
        std::vector<std::string> defines,
        std::vector<std::filesystem::path> user_includes,
        std::vector<std::filesystem::path> system_includes
    )
        : _name(std::move(name))
        , _compiler(compiler)
        , _platform(std::move(platform))
        , _architecture(std::move(architecture))
        , _flags(std::move(flags))
        , _defines(std::move(defines))
        , _user_includes(std::move(user_includes))
        , _system_includes(std::move(system_includes))
    {}

    const std::string& Configuration::name() const
    {
        return _name;
    }

    const std::string& Configuration::platform() const
    {
        return _platform;
    }

    const std::string& Configuration::architecture() const
    {
        return _architecture;
    }

    CompilerType Configuration::compiler() const
    {
        return _compiler;
    }

    const std::vector<std::string>& Configuration::flags() const
    {
        return _flags;
    }

    const std::vector<std::string>& Configuration::defines() const
    {
        return _defines;
    }

    const std::vector<std::filesystem::path>& Configuration::userIncludes() const
    {
        return _user_includes;
    }

    const std::vector<std::filesystem::path>& Configuration::systemIncludes() const
    {
        return _system_includes;
    }
}
