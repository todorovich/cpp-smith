#include "Executable.hpp"

#include "Project.hpp"
#include "artifacts/shared-library/SharedLibrary.hpp"
#include "artifacts/static-library/StaticLibrary.hpp"

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

        const auto configuration_directory = configuration->projectDirectory()
            / configuration->buildDirectory()
            / getCoordinates().artifact_name
            / configuration->name();

        std::vector<std::unique_ptr<Linkable>> linkableFiles;
        for (const auto& compilationUnit : compilationUnits)
        {
            linkableFiles.emplace_back(
                compiler_probe->compile(
                    compilationUnit.get(),
                    configuration_directory / configuration->objectDirectory()
                )
            );
        }

        for (const auto dependency : getDependencies())
        {
            const auto& artifact = _parent.getArtifact(dependency);

            if (artifact.is<SharedLibrary>())
            {
                const SharedLibrary& sharedLibrary = artifact.as<SharedLibrary>();
                //Linkable linkable =

            }
            else if (artifact.is<StaticLibrary>())
            {
                const StaticLibrary& staticLibrary = artifact.as<StaticLibrary>();
            }

            logger.print("Dependency: {}", artifact.getCoordinates());
        }

        compiler_probe->link(
            linkableFiles,
            configuration_directory / configuration->binaryDirectory(),
            std::string { getCoordinates() .artifact_name + ".exe" }
        );
    }
}