#pragma once

#include <filesystem>
#include <vector>

#include "artifacts/Artifact.hpp"

namespace cpp_smith
{
    class Configuration;

    class Executable final : public Artifact
    {
        std::vector<std::filesystem::path> _sources;

      public:
        Executable(
            Project& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
        )
            : Artifact(project, artifactCoordinate, dependencies, ArtifactType::of<Executable>())
            , _sources(sources)
        {}

        void create(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const override;

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}

