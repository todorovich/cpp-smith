#pragma once

#include <filesystem>
#include <vector>

#include "build/artifacts/Artifact.hpp"
#include "compile/model/Linkable.hpp"
#include "log/Logger.hpp"

namespace cpp_smith
{
    class SharedLibrary;

    template <>
    struct TypeKey<SharedLibrary>
    {
        static constexpr std::string_view value = "cpp_smith::SharedLibrary";
    };

    class SharedLibrary final : public Artifact
    {
        inline static logging::Logger logger = logging::Logger::defaultLogger("cpp_smith::SharedLibrary");

        const std::vector<std::filesystem::path> _sources;

      public:
        SharedLibrary(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinates,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
         )
             : Artifact(project, artifactCoordinates, dependencies, TypeId::of<SharedLibrary>())
             , _sources(sources)
        {}

        void create(const Configuration* configuration) const override;

        SharedLibraryFile getSharedLibraryFile(const Configuration* configuration) const;

        [[nodiscard]    ] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}
