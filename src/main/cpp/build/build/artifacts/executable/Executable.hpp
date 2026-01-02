#pragma once

#include <filesystem>
#include <vector>

#include "build/ProjectInterface.hpp"
#include "build/artifacts/Artifact.hpp"
#include "log/Logger.hpp"

namespace cpp_smith
{
    class Configuration;

    // TODO: This should be in compile not cpp_smith
    class Executable final : public Artifact
    {
        inline static logging::Logger logger = logging::Logger::defaultLogger("cpp_smith::Executable");

        std::vector<std::filesystem::path> _sources;

      public:
        Executable(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
        )
            : Artifact(project, artifactCoordinate, dependencies, ArtifactType::of<Executable>())
            , _sources(sources)
        {}

        void create(const Configuration* configuration) const override;

        std::filesystem::path getExecutablePath(const Configuration* configuration) const;

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}

