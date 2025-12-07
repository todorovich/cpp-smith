#include "Project.hpp"

#include "Exceptions.hpp"
#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/executable/ExecutableBuilder.hpp"

#include <format>

namespace cpp_smith
{
    Project& Project::accept(Configuration&& config)
    {
        _configurations.try_emplace(config.name(), std::move(config));
        return *this;
    }

    Project& Project::accept(std::unique_ptr<Artifact> artifact)
    {
        _artifacts.try_emplace(artifact->name(), std::move(artifact));
        return *this;
    }

    const Configuration& Project::getConfiguration(const std::string& name) const
    {
        try
        {
            return _configurations.at(name);
        }
        catch (const std::out_of_range&)
        {
            throw exceptions::NotFound(
                std::format("No configuration exist with the name: {}", name)
            );
        }

    }
    const std::filesystem::path& Project::getProjectDirectory() const
    {
        return _project_directory;
    }

    const std::filesystem::path& Project::getBuildDirectory() const
    {
        return _build_directory;
    }

    const TransparentUnorderedMap<std::string, Configuration>& Project::getConfigurations() const
    {
        return _configurations;
    }

    const std::filesystem::path& Project::getInstallDirectory() const
    {
        return _binary_directory;
    }

    Project& Project::withRootDirectory(const std::filesystem::path& project_directory)
    {
        _project_directory = project_directory;
        _build_directory = project_directory/"build/obj";
        _binary_directory = project_directory/"build/bin";
        _library_directory = project_directory/"build/bin";
        return *this;
    }
}