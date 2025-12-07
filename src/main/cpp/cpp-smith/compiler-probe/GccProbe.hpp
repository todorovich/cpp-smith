#pragma once

#include "CompilerProbe.hpp"
#include "ProbeUtils.hpp"


namespace cpp_smith
{
    class TranslationUnit;
    class Configuration;

    class GccProbe final : public CompilerProbe
    {
    public:
        // TODO : check that its gcc 14+ when you init
        GccProbe() = default;

        [[nodiscard]] std::string name() const override
        {
            return "gcc";
        }

        [[nodiscard]] std::filesystem::path findCompiler() const override
        {
            return "/usr/bin/g++";
        }

        [[nodiscard]] std::vector<std::filesystem::path> getSystemIncludes() const override
        {
            return ParseSystemIncludeSearchPaths("g++ -std=gnu++23 -E -x c++ /dev/null -v");
        }

        [[nodiscard]] std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>> getDependencies(
            const std::vector<std::string>& compiler_arguments,
            const std::filesystem::path& translation_unit_path
        ) const override;

        [[nodiscard]] bool exists() override;
        [[nodiscard]] std::string version() override;

        void build(TranslationUnit* translationUnit, const fs::path& build_directory) const override;
        
        void link(
            const std::span<std::unique_ptr<TranslationUnit>>& translation_units,
            const std::filesystem::path& install_directory,
            const std::string& filename
        ) const override;
    };
} // namespace cpp_smith
