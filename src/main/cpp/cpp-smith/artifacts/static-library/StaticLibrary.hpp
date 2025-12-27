#pragma once

#include <filesystem>
#include <vector>

#include "artifacts/Artifact.hpp"

namespace cpp_smith
{
    class StaticLibrary final : public Artifact
    {
        std::vector<std::filesystem::path> _sources;

    public:
        StaticLibrary(ArtifactCoordinates artifactCoordinates, std::vector<std::filesystem::path> sources)
            : Artifact(std::move(artifactCoordinates))
            , _sources(std::move(sources))
        {}

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const override
        {
            return _sources;
        }

        void build(const Configuration* configuration,
                   const std::filesystem::path& build_directory,
                   const std::filesystem::path& install_directory) const override
        {
            // TODO: Implement Me
            static_assert(true, "Not Implemented.");
        }
    };
}
