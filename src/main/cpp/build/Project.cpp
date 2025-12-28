#include "Project.hpp"

#include <format>

#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/executable/ExecutableBuilder.hpp"
#include "faults.hpp"

namespace cpp_smith
{
    Project& Project::accept(Configuration&& config)
    {
        _configurations.try_emplace(config.name(), std::move(config));
        return *this;
    }

    Project& Project::accept(std::unique_ptr<Artifact> artifact)
    {
        _artifacts.try_emplace(artifact->getCoordinates(), std::move(artifact));
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
            throw faults::missing::Configuration(
                std::format("No configuration exist with the name: {}", name)
            );
        }
    }

    const std::filesystem::path& Project::getProjectDirectory() const
    {
        return _project_directory;
    }

    const TransparentUnorderedMap<std::string, Configuration>& Project::getConfigurations() const
    {
        return _configurations;
    }

    const ProjectCoordinates& Project::getProjectCoordinates() const
    {
        return _project_coordinate;
    }

    Project& Project::withRootDirectory(const std::filesystem::path& project_directory)
    {
        _project_directory = project_directory;

        return *this;
    }
}