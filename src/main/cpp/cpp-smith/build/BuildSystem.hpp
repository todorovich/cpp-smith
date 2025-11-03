#pragma once

#include "Configuration.hpp"
#include "ConfigurationBuilder.hpp"

#include "artifacts/Artifact.hpp"
#include "artifacts/ArtifactBuilder.hpp"

#include <memory>
#include <string>
#include <unordered_map>

namespace cpp_smith
{
    class BuildSystem
    {
        std::unordered_map<std::string, Configuration> _configurations;
        std::unordered_map<std::string, std::unique_ptr<Artifact>> _artifacts;

    public:
        // Configuration DSL
        ConfigurationBuilder configuration(const std::string& name);

        // Store a finalized Configuration
        BuildSystem& add(Configuration&& config);

        // Artifact DSL
        template<typename T>
        ArtifactBuilder<T> artifact(const std::string& name)
        {
            return ArtifactBuilder<T>(*this, name);
        }

        // Store a finalized Artifact
        BuildSystem& addArtifact(std::unique_ptr<Artifact> artifact);

        // Accessors
        const Configuration& getConfiguration(const std::string& name) const;
        const std::unordered_map<std::string, Configuration>& configurations() const;

        const Artifact& getArtifact(const std::string& name) const
        {
            return *(_artifacts.at(name));
        };

        const std::unordered_map<std::string, std::unique_ptr<Artifact>>& artifacts() const
        {
            return _artifacts;
        };

        // Finalize the build: generate tasks, run dependency resolution, etc.
        void build()
        {
            /*TODO*/
        };
    };
}

