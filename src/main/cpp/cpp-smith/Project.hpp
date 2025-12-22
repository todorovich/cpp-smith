#pragma once

#include "Configuration.hpp"
#include "TransparentContainers.hpp"
#include "artifacts/Artifact.hpp"
#include "artifacts/ArtifactBuilder.hpp"

#include <memory>
#include <ranges>
#include <string>

namespace cpp_smith
{
    class Project
    {
        TransparentUnorderedMap<std::string, Configuration> _configurations;
        TransparentUnorderedMap<std::string, std::unique_ptr<Artifact>> _artifacts;

        std::filesystem::path _project_directory;

        template<typename T>
        ArtifactBuilder<T> define(const std::string& name, T*)
        {
            return ArtifactBuilder<T>(*this, name);
        }

        ConfigurationBuilder define(const std::string& name, Configuration*)
        {
            const std::filesystem::path namePath{name};
            return ConfigurationBuilder{this, name}
                .withProjectDirectory(_project_directory)
                .withBuildDirectory(_project_directory/"build"/namePath/"obj")
                .withBinaryDirectory(_project_directory/"build"/namePath/"bin")
                .withLibraryDirectory(_project_directory/"build"/namePath/"lib");
        }

    public:
        template <typename T>
        auto define(const std::string& name)
        {
            // Pass a null pointer just to drive overload resolution
            return define(name, static_cast<T*>(nullptr));
        }

        Project& accept(std::unique_ptr<Artifact> artifact);

        Project& accept(Configuration&& config);

        Project& withRootDirectory(const std::filesystem::path& project_directory);

        [[nodiscard]] const Artifact& getArtifact(const std::string& name) const
        {
            return *_artifacts.at(name);
        };

        [[nodiscard]] const TransparentUnorderedMap<std::string, std::unique_ptr<Artifact>>& getArtifacts() const
        {
            return _artifacts;
        };

        [[nodiscard]] const Configuration& getConfiguration(const std::string& name) const;
        [[nodiscard]] const std::filesystem::path& getProjectDirectory() const;
        [[nodiscard]] const TransparentUnorderedMap<std::string, Configuration>& getConfigurations() const;



        void build()
        {
            for (const auto& artifact : _artifacts | std::views::values)
            {
                for (const auto& configuration : _configurations | std::views::values)
                {
                    artifact->build(
                        &configuration, configuration.buildDirectory(), configuration.binaryDirectory()
                    );
                }
            }
        }
    };
}

