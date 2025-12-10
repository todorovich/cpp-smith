#include "GccProbe.hpp"

#include "Exceptions.hpp"
#include "TransparentContainers.hpp"
#include "source-graph/TranslationUnit.hpp"

#include <print>

namespace cpp_smith
{
    std::pair<std::vector<std::filesystem::path>, std::vector<std::filesystem::path>> GccProbe::getDependencies(
        const std::vector<std::string>& compiler_arguments,
        const std::filesystem::path& translation_unit_path
    ) const
    {
        const std::string base = "g++ -std=gnu++23 -x c++ -M";

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

        const auto all_dependencies = ParseMakeStyleDependencies(all_output);
        auto project_only_deps      = ParseMakeStyleDependencies(proj_output);

        TransparentUnorderedSet<std::string> project_normalized;
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

    void GccProbe::build(TranslationUnit* translationUnit, const fs::path& build_directory) const
    {
        namespace fs = std::filesystem;

        const fs::path source = translationUnit->getSourceFile().path();

        // Decide output directory and file
        const fs::path object_filepath = build_directory / (source.stem().string() + ".o");
        const fs::path dependency_filepath = build_directory / (source.stem().string() + ".d");

        // Ensure output directory exists
        std::error_code ec;
        fs::create_directories(build_directory, ec);

        auto quote = [](const fs::path& p)
        {
            // Basic quoting for paths with spaces (Linux/WSL)
            const std::string s = p.string();
            return "'" + s + "'";
        };

        // Collect project include directories from direct header dependencies
        TransparentUnorderedSet<std::string> includeDirsSet;
        for (const auto& dep : translationUnit->getSourceFile().directDependencies())
        {
            if (const auto dir = dep.parent_path().lexically_normal().string();
                !dir.empty()
            )
            {
                includeDirsSet.insert(dir);
            }
        }

        // Build command
        std::string command = std::format(
            "{} -std=gnu++23 -x c++ -c {} -o {} -MMD -MP -MF {}",
            quote(findCompiler()),
            quote(source),
            quote(object_filepath),
            quote(dependency_filepath)
        );

        // Project include dirs (-I)
        for (const auto& dir : includeDirsSet)
        {
            command = std::format(
                "{} -I '{}'",
                command, dir
            );
        }

        // System include dirs (-isystem)
        for (const auto& sysInc : getSystemIncludes())
        {
            command = std::format(
                "{} -isystem {}",
                command, quote(sysInc)
            );
        }

        const std::string output = ExecuteCommandAndCaptureOutput(command + " 2>&1");

        // Since ExecuteCommandAndCaptureOutput doesn't give us the exit code here,
        // do a quick existence check for the object file to determine success.
        if (!fs::exists(object_filepath))
        {
            throw exceptions::CompilationError{
                std::format(
                    "Failed to compile translation unit:\n"
                    "Command:\n"
                    "{}\n"
                    "Output:\n"
                    "{}\n",
                    command,
                    output
                )
            };
        }

        if (!fs::exists(dependency_filepath))
        {
            throw exceptions::CompilationError{
                std::format(
                    "Failed to compile translation unit [no dependency file]:\n"
                    "Command:\n"
                    "{}\n"
                    "Output:\n"
                    "{}\n",
                    command,
                    output
                )
            };
        }

        translationUnit->setObjectFile(object_filepath);
        translationUnit->setDependencyFile(dependency_filepath);
    }

    void GccProbe::link(
        const std::span<std::unique_ptr<TranslationUnit>>& translation_units,
        const std::filesystem::path& install_directory,
        const std::string& filename
    ) const
    {
        if (translation_units.empty())
        {
            throw std::invalid_argument("No translation units to link");
        }

        const auto firstConfiguration = translation_units.front()->getConfiguration();

        for (const auto& translation_unit : translation_units)
        {
            if (translation_unit->getConfiguration() != firstConfiguration)
            {
                throw exceptions::InvalidInput("All translation units must share the same configuration");
            }
        }

        // Ensure output directory exists
        std::error_code ec;
        fs::create_directories(install_directory, ec);

        std::ostringstream cmd;
        cmd << "g++ -o '" << install_directory.string() << '/' << filename << "'";

        for (const auto& unit : translation_units)
        {
            if (!unit->getObjectFile().empty())
            {
                cmd << " '" << unit.get()->getObjectFile().string() << "'";
            }
        }

        const std::string command = cmd.str();

        std::println("{}", command);

        const std::string output = ExecuteCommandAndCaptureOutput(command + " 2>&1");

        if (!std::filesystem::exists(install_directory/filename))
        {
            throw exceptions::LinkingError(
                std::format(
                    "Failed to link executable:\nCommand:\n{}\nOutput:\n{}\n",
                    command,
                    output
                )
            );
        }
    }

    bool GccProbe::exists()
    {
        const auto [result, output] = ExecuteCommand("g++ -dumpfullversion 2>&1");

        return result == 0;
    }

    std::string GccProbe::version()
    {
        const auto [result, output] = ExecuteCommand("g++ -dumpfullversion 2>&1");
        if (result == 0)
        {
            return output;
        }
        else
        {
            throw exceptions::FailedToGetCompilerVersion(
                std::format(
                    "Command Execution Failed\nCommand: g++ --version 2>&1\nOutput: {}\n",
                    output
                )
            );
        }
    }
} // namespace cpp_smith