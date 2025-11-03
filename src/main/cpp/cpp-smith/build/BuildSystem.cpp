#include "BuildSystem.hpp"

#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/ExecutableBuilder.hpp"
#include "artifacts/StaticLibraryBuilder.hpp"
#include "artifacts/SharedLibraryBuilder.hpp"

namespace cpp_smith
{
    ConfigurationBuilder BuildSystem::configuration(const std::string& name)
    {
        return {this, name};
    }

    BuildSystem& BuildSystem::add(Configuration&& config)
    {
        _configurations.emplace(config.name(), std::move(config));
        return *this;
    }

    BuildSystem& BuildSystem::addArtifact(std::unique_ptr<Artifact> artifact)
    {
        _artifacts.emplace(artifact->name(), std::move(artifact));
        return *this;
    }

    const Configuration& BuildSystem::getConfiguration(const std::string& name) const
    {
        return _configurations.at(name); // todo: this throws a bs exception, would be nice to throw something that says where you made the bad call
    }

    const std::unordered_map<std::string, Configuration>& BuildSystem::configurations() const
    {
        return _configurations;
    }
}