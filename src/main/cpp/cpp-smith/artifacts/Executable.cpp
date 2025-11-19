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
            name().c_str(), compiler, build_directory.c_str()
        );

        CompilerProbe* compiler_probe;
        switch (compiler)
        {
            case CompilerType::GCC:
                compiler_probe = new GccProbe{};
                break;
            case CompilerType::CLANG: // FALLTHROUGH
            case CompilerType::MSVC:
                throw std::runtime_error("Not implemented yet");
            default:
                throw std::logic_error("Unknown compiler type");
        }

        // TODO: cache all the things!
        std::vector<TranslationUnit*> translationUnits;
        for (const auto& source : sources())
        {
            auto* translation_unit = new TranslationUnit {
                SourceFile::from(source, compiler_probe), *configuration
            };

            translationUnits.push_back(translation_unit);
        }

        for (const auto& translationUnit : translationUnits)
        {
            compiler_probe->build(translationUnit, build_directory);
        }

        compiler_probe->link(
            translationUnits,
            install_directory,
            std::string { name() + ".exe" }
        );
    }
}