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
        Executable(ArtifactCoordinates artifactCoordinate, std::vector<std::filesystem::path> _sources)
            : Artifact(std::move(artifactCoordinate))
            , _sources(std::move(_sources))
        {}

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const override
        {
            return _sources;
        }

        void build(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const override;
    };
}

