#include "StaticLibrary.hpp"

#include <cstdlib>
#include <string>

#include "compile/compiler-probe/GccProbe.hpp"
#include "compile/model/CompilationUnit.hpp"

namespace cpp_smith
{
    void StaticLibrary::create(const Configuration* configuration) const
    {
        const auto& compiler = configuration->compiler();

        logger.print(
            "\nBuilding Static Library\nArtifact Coordinates: {}\nCompiler: {}\nBuild Directory: {}\n\n",
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

        const auto lib_dir = configuration_directory / configuration->libraryDirectory();
        std::filesystem::create_directories(lib_dir);

        const auto out_archive = lib_dir / std::string{ "lib" + getCoordinates().artifact_name + ".a" };

        std::string command = "ar rcs \"" + out_archive.string() + "\"";
        for (const auto& linkable : linkableFiles)
        {
            command += " \"" + linkable->getObjectFile().string() + "\"";
        }

        logger.print("Archiving: {}", out_archive.c_str());
        const int rc = std::system(command.c_str());
        if (rc != 0)
        {
            throw std::runtime_error("Failed to create static library archive: " + out_archive.string());
        }
    }
}