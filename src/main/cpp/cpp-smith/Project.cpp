#include "Project.hpp"

#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/ExecutableBuilder.hpp"

namespace cpp_smith
{
    Project& Project::accept(Configuration&& config)
    {
        _configurations.emplace(config.name(), std::move(config));
        return *this;
    }

    Project& Project::accept(std::unique_ptr<Artifact> artifact)
    {
        _artifacts.emplace(artifact->name(), std::move(artifact));
        return *this;
    }

    const Configuration& Project::getConfiguration(const std::string& name) const
    {
        return _configurations.at(name); // todo: this throws a bs exception, would be nice to throw something that says
                                         // where you made the bad call
    }
    const std::filesystem::path& Project::getProjectDirectory() const
    {
        return _project_directory;
    }

    const std::filesystem::path& Project::getBuildDirectory() const
    {
        return _build_directory;
    }

    const std::filesystem::path& Project::getInstallDirectory() const
    {
        return _binary_directory;
    }

    const std::unordered_map<std::string, Configuration>& Project::getConfigurations() const
    {
        return _configurations;
    }

    Project& Project::withRootDirectory(std::filesystem::path project_directory)
    {
        _project_directory = project_directory;
        _build_directory = project_directory/"build/obj";
        _binary_directory = project_directory/"build/bin";
        _library_directory = project_directory/"build/bin";
        return *this;
    }
}