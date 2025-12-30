#pragma once

#include <memory>
#include <ranges>
#include <string>

#include "artifacts/Artifact.hpp"
#include "artifacts/ArtifactBuilder.hpp"
#include "Configuration.hpp"
#include "ProjectCoordinates.hpp"
#include "containers/TransparentContainers.hpp"

namespace cpp_smith
{
    class Project
    {
        TransparentUnorderedMap<std::string, Configuration> _configurations;
        std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>> _artifacts;

        std::filesystem::path _project_directory;
        ProjectCoordinates _project_coordinate;

        template<typename T>
        ArtifactBuilder<T> _define(const std::string& name, T*)
        {
            return ArtifactBuilder<T>(*this, name);
        }

        ConfigurationBuilder _define(const std::string& configurationName, Configuration*)
        {
            const std::filesystem::path namePath{configurationName};

            return ConfigurationBuilder{this, configurationName}
                .withProjectDirectory(_project_directory)
                .withBuildDirectory(
                    std::filesystem::path{"build"}
                        / _project_coordinate.group
                        / _project_coordinate.project
                        / std::format("{}",_project_coordinate.version)
                )
                .withBinaryDirectory("bin")
                .withLibraryDirectory("lib")
                .withObjectDirectory("obj");
        }

    public:
        explicit Project(ProjectCoordinates&& projectCoordinate)
            : _project_coordinate(std::move(projectCoordinate))
        {}

        explicit Project(const ProjectCoordinates& projectCoordinate)
            : _project_coordinate(projectCoordinate)
        {}

        template <typename T>
        auto define(const std::string& name)
        {
            // Pass a null pointer just to drive overload resolution
            return _define(name, static_cast<T*>(nullptr));
        }

        Project& accept(std::unique_ptr<Artifact> artifact);

        Project& accept(Configuration&& config);

        Project& withRootDirectory(const std::filesystem::path& project_directory);

        [[nodiscard]] const Artifact& getArtifact(const std::string& name) const
        {
            return *_artifacts.at({_project_coordinate, name});
        };

        [[nodiscard]] const Artifact& getArtifact(const ArtifactCoordinates& artifactCoordinates) const
        {
            return *_artifacts.at(artifactCoordinates);
        };

        [[nodiscard]] const std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>>&
            getArtifacts() const
        {
            return _artifacts;
        };

        [[nodiscard]] const Configuration& getConfiguration(const std::string& name) const;
        [[nodiscard]] const TransparentUnorderedMap<std::string, Configuration>& getConfigurations() const;
        [[nodiscard]] const ProjectCoordinates& getProjectCoordinates() const;
        [[nodiscard]] const std::filesystem::path& getProjectDirectory() const;

        void build()
        {
            for (const auto& artifact : _artifacts | std::views::values)
            {
                for (const auto& configuration : _configurations | std::views::values)
                {
                    artifact->create(&configuration);
                }
            }
        }
    };
}
