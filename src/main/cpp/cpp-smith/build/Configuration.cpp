#include "Configuration.hpp"

Configuration::Configuration(
    std::string name,
    std::filesystem::path compiler,
    std::vector<std::string> flags,
    std::vector<std::string> defines,
    std::vector<std::filesystem::path> user_includes,
    std::vector<std::filesystem::path> system_includes,
    std::string platform,
    std::string architecture
)
    : _name(std::move(name))
    , _compiler(std::move(compiler))
    , _flags(std::move(flags))
    , _defines(std::move(defines))
    , _user_includes(std::move(user_includes))
    , _system_includes(std::move(system_includes))
    , _platform(std::move(platform))
    , _architecture(std::move(architecture))
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

const std::filesystem::path& Configuration::compiler() const
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
