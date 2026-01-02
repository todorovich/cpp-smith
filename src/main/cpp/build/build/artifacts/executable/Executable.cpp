#include "Executable.hpp"

#include "build/Project.hpp"
#include "build/artifacts/shared-library/SharedLibrary.hpp"
#include "build/artifacts/static-library/StaticLibrary.hpp"

#include "compile/compiler-probe/GccProbe.hpp"
#include "compile/model/CompilationUnit.hpp"

namespace cpp_smith
{
    void Executable::create(const Configuration* configuration) const
    {
        const auto& compiler = configuration->compiler();

        logger.print(
            "\nBuilding Executable\nArtifact Coordinates: {}\nCompiler: {}\nBuild Directory: {}\n\n",
            getCoordinates(), compiler, configuration->buildDirectory().c_str()
        );

        std::unique_ptr<CompilerProbe> compiler_probe;
        switch (compiler)
        {
            using enum CompilerType;
            case GCC:
                compiler_probe = std::make_unique<GccProbe>();
                break;
            case CLANG: // FALLTHROUGH
            case MSVC:
                static_assert(true, "Not implemented yet");
            default:
                static_assert(true, "Unknown compiler type");
        }

        std::vector<std::unique_ptr<CompilationUnit>> compilationUnits;
        for (const auto& source : _sources)
        {
            compilationUnits.emplace_back(
                std::make_unique<CompilationUnit>(SourceFile::from(source, compiler_probe.get()), *configuration)
            );
        }

        const auto configuration_directory = configuration->getBaseOutputDirectory(getCoordinates().artifact_name);

        std::vector<ObjectFile> object_files;
        object_files.reserve(compilationUnits.size());

        std::vector<Linkable*> linkables;
        linkables.reserve(compilationUnits.size() + getDependencies().size());

        for (const auto& compilationUnit : compilationUnits)
        {
            object_files.emplace_back(
                compiler_probe->compile(
                    compilationUnit.get(),
                    configuration_directory / configuration->objectDirectory()
                )
            );

            linkables.push_back(&object_files.back());
        }

        std::vector<SharedLibraryFile> shared_library_files;
        std::vector<StaticLibraryFile> static_library_files;
        shared_library_files.reserve(getDependencies().size());
        static_library_files.reserve(getDependencies().size());

        for (const auto dependency : getDependencies())
        {
            const auto& artifact = _parent.getArtifact(dependency);

            logger.print("Dependency: {}", artifact.getCoordinates());

            if (artifact.is<SharedLibrary>())
            {
                const SharedLibrary& shared_library = artifact.as<SharedLibrary>();

                shared_library_files.emplace_back(shared_library.getSharedLibraryFile(configuration));
                linkables.push_back(&shared_library_files.back());
            }
            else if (artifact.is<StaticLibrary>())
            {
                const StaticLibrary& static_library = artifact.as<StaticLibrary>();

                static_library_files.emplace_back(static_library.getStaticLibraryFile(configuration));
                linkables.push_back(&static_library_files.back());
            }
        }

        compiler_probe->link(
            linkables,
            configuration_directory / configuration->binaryDirectory(),
            std::string { getCoordinates().artifact_name + ".exe" },
            LinkingOutput::Executable
        );
    }

    std::filesystem::path Executable::getExecutablePath(const Configuration* configuration) const
    {
        return configuration->getBaseOutputDirectory(getCoordinates().artifact_name)
            / configuration->binaryDirectory()
            / std::string { getCoordinates().artifact_name + ".exe" };
    }
}
