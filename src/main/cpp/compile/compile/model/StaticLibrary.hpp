#pragma once

#include <filesystem>
#include <vector>

#include "build/artifacts/Artifact.hpp"
#include "compile/model/Linkable.hpp"
#include "log/Logger.hpp"

namespace cpp_smith
{
    class StaticLibrary;

    template <>
    struct TypeKey<StaticLibrary>
    {
        static constexpr std::string_view value = "cpp_smith::StaticLibrary";
    };

    // TODO: This should be in compile not cpp_smith
    class StaticLibrary final : public Artifact
    {
        // TODO: seems like I have to take loggers in everywhere in order to print the output of tests to one logger
        //      alt is capturing all terminal output, which has already been explored and sucks.
        //      second alt could be to read this in the test and attach it to output. Although by default its still
        //      going to the console... so that would have to be fixed.
        inline static logging::Logger logger = logging::Logger::defaultLogger("cpp_smith::StaticLibrary");

        const std::vector<std::filesystem::path> _sources;

      public:
        StaticLibrary(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinates,
            const std::vector<ArtifactCoordinates>& dependencies,
            const std::vector<std::filesystem::path>& sources
        )
            : Artifact(project, artifactCoordinates, std::move(dependencies), TypeId::of<StaticLibrary>())
            , _sources(sources)
        {}
        void create(const Configuration* configuration) const override;

        StaticLibraryFile getStaticLibraryFile(const Configuration* configuration) const;

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const { return _sources; }
    };
}
