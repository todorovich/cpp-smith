#pragma once

#include "artifacts/Artifact.hpp"

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class SharedLibrary final : public Artifact
    {
        const std::vector<std::filesystem::path> _sources;

      public:
        SharedLibrary(
            Project& project,
            const ArtifactCoordinates& artifactCoordinates,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
         )
             : Artifact(project, artifactCoordinates, dependencies, ArtifactType::of<SharedLibrary>())
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
