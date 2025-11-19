#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace cpp_smith
{
    class TranslationUnit;
    class Configuration;

    class CompilerProbe {
    public:
        virtual ~CompilerProbe() = default;

        // TODO: add an exists() function?
        [[nodiscard]] virtual std::string name() const = 0;
        [[nodiscard]] virtual std::filesystem::path findCompiler() const = 0;
        [[nodiscard]] virtual std::vector<std::filesystem::path> getSystemIncludes() const = 0;

        virtual void build(TranslationUnit* translationUnit, const std::filesystem::path& build_directory) const = 0;

        virtual void link(
            const std::vector<TranslationUnit*>& translation_units,
            const std::filesystem::path& install_directory,
            const std::string& filename
        ) const = 0;

        [[nodiscard]] virtual std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>>
        getDependencies(
            const std::vector<std::string>& compiler_arguments, const std::filesystem::path& translation_unit_path
        ) const = 0;
    };
}

