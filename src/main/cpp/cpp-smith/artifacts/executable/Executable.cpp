#include "Executable.hpp"

#include "compiler-probe/GccProbe.hpp"
#include "source-graph/TranslationUnit.hpp"

#include <print>

namespace cpp_smith
{
    void Executable::build(const Configuration* configuration,
                           const std::filesystem::path& build_directory,
                           const std::filesystem::path& install_directory) const
    {
        const auto& compiler = configuration->compiler();

        std::println(
            "\nBuilding Executable\nName: {}\nCompiler: {}\nBuild Directory: {}\n",
            name(), compiler, build_directory.c_str()
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

        std::vector<std::unique_ptr<TranslationUnit>> translationUnits;
        for (const auto& source : sources())
        {
            translationUnits.emplace_back(
                std::make_unique<TranslationUnit>(SourceFile::from(source, compiler_probe.get()), *configuration)
            );
        }

        for (const auto& translationUnit : translationUnits)
        {
            compiler_probe->build(translationUnit.get(), build_directory);
        }

        compiler_probe->link(
            translationUnits,
            install_directory,
            std::string { name() + ".exe" }
            );
    }
}