#pragma once

#include <filesystem>
#include <vector>

#include "ArtifactCoordinates.hpp"

namespace cpp_smith
{
    class Configuration;
    class CompilerProbe;

    class Artifact
    {
        const ArtifactCoordinates _artifact_coordinate;

      protected:
        explicit Artifact(ArtifactCoordinates artifactCoordinate)
            : _artifact_coordinate(std::move(artifactCoordinate))
        {}

      public:
        virtual ~Artifact() = default;

        [[nodiscard]] const ArtifactCoordinates& getArtifactCoordinate() const { return _artifact_coordinate; }

        // Return the translation units that define this artifact.
        [[nodiscard]] virtual const std::vector<std::filesystem::path>& sources() const = 0;

        virtual void build(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const = 0;
    };
}
