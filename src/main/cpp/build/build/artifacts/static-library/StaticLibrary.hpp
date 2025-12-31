#pragma once

#include <filesystem>
#include <vector>

#include "build/artifacts/Artifact.hpp"
#include "log/Logger.hpp"

namespace cpp_smith
{
    class StaticLibrary final : public Artifact
    {
        inline static logging::Logger logger = logging::Logger::defaultLogger("cpp_smith::StaticLibrary");

        const std::vector<std::filesystem::path> _sources;

      public:
        StaticLibrary(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinates,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
        )
            : Artifact(project, artifactCoordinates, std::move(dependencies), ArtifactType::of<StaticLibrary>())
            , _sources(sources)
        {}
        void create(const Configuration* configuration) const override;

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}
