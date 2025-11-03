#pragma once

#include "CompilerProbe.hpp"
#include "ProbeUtils.hpp"

#include <unordered_set>

class GccProbe final : public CompilerProbe
{
public:
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
        return ParseSystemIncludeSearchPaths("g++ -std=c++23 -E -x c++ /dev/null -v");
    }

    [[nodiscard]] std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>> getDependencies(
        const std::vector<std::string>& compiler_arguments,
        const std::filesystem::path& translation_unit_path
    ) const override
    {
        const std::string base = "g++ -std=c++23 -x c++ -M";

        std::string joined_arguments;
        for (const auto& argument : compiler_arguments)
        {
            joined_arguments += ' ';
            joined_arguments += argument;
        }

        const std::string all_output  = ExecuteCommandAndCaptureOutput(
            base + "D -MF - "  + joined_arguments + " -c " + translation_unit_path.string()
        );

        const std::string proj_output = ExecuteCommandAndCaptureOutput(
            base + "MD -MF - " + joined_arguments + " -c " + translation_unit_path.string()
        );

        const auto all_dependencies  = ParseMakeStyleDependencies(all_output);
        auto project_only_deps = ParseMakeStyleDependencies(proj_output);

        std::unordered_set<std::string> project_normalized;
        for (const auto& p : project_only_deps)
        {
            project_normalized.insert(p.lexically_normal().string());
        }

        std::vector<std::filesystem::path> system_only;
        for (const auto& path : all_dependencies)
        {
            if (!project_normalized.contains(path.lexically_normal().string()))
            {
                system_only.push_back(path);
            }
        }

        return {std::move(project_only_deps), std::move(system_only) };
    }
};
