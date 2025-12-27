#pragma once

#include <filesystem>
#include <vector>

#include "artifacts/Artifact.hpp"

namespace cpp_smith
{
    class StaticLibrary final : public Artifact
    {
        const std::vector<std::filesystem::path> _sources;

      public:
        StaticLibrary(
            Project& project,
            const ArtifactCoordinates& artifactCoordinates,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
        )
            : Artifact(project, artifactCoordinates, std::move(dependencies), ArtifactType::of<StaticLibrary>())
            , _sources(sources)
        {}

        void create(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const override
        {
            // TODO: Implement Me
            static_assert(true, "Not Implemented.");
        }

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}
