#include "BuildSystem.hpp"

ConfigurationBuilder BuildSystem::configuration(const std::string& name)
{
    return ConfigurationBuilder(*this, name);
}

BuildSystem& BuildSystem::add(Configuration config)
{
    _configurations.emplace(config.name(), std::move(config));
    return *this;
}

const Configuration& BuildSystem::getConfiguration(const std::string& name) const
{
    return _configurations.at(name);
}

const std::unordered_map<std::string, Configuration>& BuildSystem::configurations() const
{
    return _configurations;
}

void BuildSystem::build()
{
    // TODO: actually do the build.
    // Optional: finalize, validate configs, generate full build DAG, etc.
}
