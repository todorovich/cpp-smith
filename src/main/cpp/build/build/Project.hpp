#pragma once

#include <memory>
#include <ranges>
#include <string>

#include "build/artifacts/Artifact.hpp"
#include "build/Configuration.hpp"
#include "build/Factory.hpp"
#include "build/ProjectInterface.hpp"
#include "build/ProjectCoordinates.hpp"
#include "containers/TransparentContainers.hpp"
#include "faults/faults.hpp"

namespace cpp_smith
{
    class CompilationConfiguration;

    class Project : public ProjectInterface
    {
        TransparentUnorderedMap<std::string, std::unique_ptr<Configuration>> _configurations;
        std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>> _artifacts;

        std::filesystem::path _project_directory;
        ProjectCoordinates _project_coordinate;

    public:
        explicit Project(ProjectCoordinates&& projectCoordinate)
            : _project_coordinate(std::move(projectCoordinate))
        {}

        explicit Project(const ProjectCoordinates& projectCoordinate)
            : _project_coordinate(projectCoordinate)
        {}

        template <typename T> requires HasFactory<T>
        auto define(std::string name)
        {
            return Factory<T>::create(*this, std::move(name));
        }

        Project& accept(std::unique_ptr<Artifact> artifact) override;

        Project& accept(std::unique_ptr<Configuration> config) override;

        Project& withRootDirectory(const std::filesystem::path& project_directory);

        [[nodiscard]] const Artifact& getArtifact(const std::string& name) const override
        {
            return *_artifacts.at({_project_coordinate, name});
        };

        [[nodiscard]] const Artifact& getArtifact(const ArtifactCoordinates& artifactCoordinates) const override
        {
            return *_artifacts.at(artifactCoordinates);
        };

        [[nodiscard]] const std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>>&
            getArtifacts() const override
        {
            return _artifacts;
        };

        template<typename T>
        const auto& getConfiguration(
            const std::string& name,
            const std::source_location sourceLocation = std::source_location::current()
        ) const
        {
            try
            {
                const auto& configuration = *_configurations.at(name).get();

                return configuration.as<T>(sourceLocation);
            }
            catch (const std::out_of_range&)
            {
                throw faults::missing::Configuration(
                    std::format("No configuration exist with the name: {}", name)
                );
            }
        }

        [[nodiscard]] const Configuration& getConfiguration(const std::string& name) const override;
        [[nodiscard]] const TransparentUnorderedMap<std::string, std::unique_ptr<Configuration>>&
            getConfigurations() const;
        [[nodiscard]] const ProjectCoordinates& getProjectCoordinates() const override;
        [[nodiscard]] const std::filesystem::path& getProjectDirectory() const override;

        void build()
        {
            for (const auto& artifact : _artifacts | std::views::values)
            {
                for (const auto& configuration : _configurations | std::views::values)
                {
                    artifact->create(configuration.get());
                }
            }
        }
    };

    template <>
    struct TypeKey<Project>
    {
        static constexpr std::string_view value = "cpp_smith::Project";
    };
}
