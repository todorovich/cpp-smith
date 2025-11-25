#pragma once

#include "configuration/Configuration.hpp"
#include "configuration/ConfigurationBuilder.hpp"

#include "artifacts/Artifact.hpp"
#include "artifacts/ArtifactBuilder.hpp"

// TODO: pull in all the artifacts? Or find a way to register artifacts, so user can write some too.

#include <memory>
#include <ranges>
#include <string>
#include <unordered_map>

namespace cpp_smith
{
    class Project
    {
        std::unordered_map<std::string, Configuration> _configurations;
        std::unordered_map<std::string, std::unique_ptr<Artifact>> _artifacts;

        // TODO:: These should end up as the defaults in each configuration. and used from there.
        std::filesystem::path _project_directory;
        std::filesystem::path _build_directory;
        std::filesystem::path _binary_directory;
        std::filesystem::path _library_directory;

        // Artifact DSL
        template<typename T>
        ArtifactBuilder<T> define(const std::string& name, T*)
        {
            return ArtifactBuilder<T>(*this, name);
        }

        // Configuration DSL
        ConfigurationBuilder define(const std::string& name, Configuration*)
        {
            return ConfigurationBuilder{this, name};
        }

    public:
        template <typename T>
        auto define(const std::string& name)
        {
            // Pass a null pointer just to drive overload resolution
            return define(name, static_cast<T*>(nullptr));
        }

        // Store a finalized Artifact
        Project& accept(std::unique_ptr<Artifact> artifact);

        // Store a finalized Configuration
        Project& accept(Configuration&& config);

        Project& withRootDirectory(std::filesystem::path project_directory);

        // Accessors
        [[nodiscard]] const Artifact& getArtifact(const std::string& name) const
        {
            return *(_artifacts.at(name));
        };

        [[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<Artifact>>& getArtifacts() const
        {
            return _artifacts;
        };

        [[nodiscard]] const Configuration& getConfiguration(const std::string& name) const;
        [[nodiscard]] const std::filesystem::path& getProjectDirectory() const;
        [[nodiscard]] const std::filesystem::path& getBuildDirectory() const;
        [[nodiscard]] const std::filesystem::path& getInstallDirectory() const;
        [[nodiscard]] const std::unordered_map<std::string, Configuration>& getConfigurations() const;

        void build()
        {
            for (const auto& artifact : _artifacts | std::views::values)
            {
                for (const auto& configuration : _configurations | std::views::values)
                {
                    artifact->build(&configuration, _build_directory, _binary_directory);
                }
            }
        }
    };
}

