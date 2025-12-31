#include "SharedLibrary.hpp"

#include "build/Project.hpp"
#include "build/artifacts/static-library/StaticLibrary.hpp"

#include "compile/compiler-probe/GccProbe.hpp"
#include "compile/model/CompilationUnit.hpp"

namespace cpp_smith
{
    void SharedLibrary::create(const Configuration* configuration) const
    {
        const auto& compiler = configuration->compiler();

        logger.print(
            "\nBuilding Shared Library\nArtifact Coordinates: {}\nCompiler: {}\nBuild Directory: {}\n\n",
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

        for (const auto& dependency : getDependencies())
        {
            const auto& artifact = _parent.getArtifact(dependency);

            // Note: for now we only log dependencies, mirroring Executable.cpp’s current state.
            // Later: convert built library artifacts into additional link inputs for the final link step.
            if (artifact.is<StaticLibrary>())
            {
                const auto& staticLibrary = artifact.as<StaticLibrary>();
                (void)staticLibrary;
            }

            logger.print("Dependency: {}", artifact.getCoordinates());
        }

        // On gcc-like toolchains, "lib<name>.so" is the conventional shared library name.
        // If/when MSVC support is added, this likely becomes "<name>.dll" (+ import .lib).
        compiler_probe->link(
            linkableFiles,
            configuration_directory / configuration->libraryDirectory(),
            std::string{ "lib" + getCoordinates().artifact_name + ".so" }
        );
    }
}