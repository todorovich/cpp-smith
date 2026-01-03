#include "compile/compiler-probe/GccProbe.hpp"
#include "compile/model/CompilationUnit.hpp"
#include "compile/model/StaticLibrary.hpp"
#include "compile/model/SharedLibrary.hpp"
#include "compile/model/CompilationConfiguration.hpp"

namespace cpp_smith
{
    void SharedLibrary::create(const Configuration* configuration) const
    {
        const auto& compilation_configuration = configuration->as<CompilationConfiguration>();

        const auto& compiler = compilation_configuration.compiler();

        logger.print(
            "\nBuilding Shared Library\nArtifact Coordinates: {}\nCompiler: {}\nBuild Directory: {}\n\n",
            getCoordinates(), compiler, compilation_configuration.buildDirectory().c_str()
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
                std::make_unique<CompilationUnit>(
                    SourceFile::from(source, compiler_probe.get()), compilation_configuration)
            );
        }

        const auto configuration_directory = compilation_configuration.getBaseOutputDirectory(getCoordinates().artifact_name);

        std::vector<ObjectFile> objectFiles;
        objectFiles.reserve(compilationUnits.size());

        std::vector<Linkable*> linkables;
        linkables.reserve(compilationUnits.size() + getDependencies().size());

        for (const auto& compilationUnit : compilationUnits)
        {
            objectFiles.emplace_back(
                compiler_probe->compile(
                    compilationUnit.get(),
                    configuration_directory / compilation_configuration.objectDirectory()
                )
            );

            linkables.push_back(&objectFiles.back());
        }

        for (const auto& dependency : getDependencies())
        {
            const auto& artifact = _parent.getArtifact(dependency);

            if (artifact.is<StaticLibrary>())
            {
                const auto& staticLibrary = artifact.as<StaticLibrary>();
                (void)staticLibrary;
            }

            logger.print("Dependency: {}", artifact.getCoordinates());
        }

        compiler_probe->link(
            linkables,
            configuration_directory / compilation_configuration.libraryDirectory(),
            std::string{ "lib" + getCoordinates().artifact_name + ".so" },
            LinkingOutput::SharedLibrary
        );
    }

    SharedLibraryFile SharedLibrary::getSharedLibraryFile(const Configuration* configuration) const
    {
        const auto& compilation_configuration = configuration->as<CompilationConfiguration>();

        return SharedLibraryFile {
            compilation_configuration.getBaseOutputDirectory(getCoordinates().artifact_name)
                / compilation_configuration.libraryDirectory()
                / std::string { "lib" + getCoordinates().artifact_name + ".so" }
        };
    }
}
