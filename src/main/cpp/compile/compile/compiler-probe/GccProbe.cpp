#include "GccProbe.hpp"

#include "faults/faults.hpp"
#include "../../../utility/containers/containers/TransparentContainers.hpp"

#include "../model/CompilationUnit.hpp"

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

        const auto [exit_code, output]  = System::ExecuteCommand(
            std::string{base + "D -MF - "  + joined_arguments + " -c -o /dev/null " + translation_unit_path.string()}
        );
        const auto all_dependencies = ParseMakeStyleDependencies(output);

        const auto [exit_code_2, output_2] = System::ExecuteCommand(
            std::string{base + "MD -MF - " + joined_arguments + " -c -o /dev/null " + translation_unit_path.string()}
        );
        auto project_only_deps= ParseMakeStyleDependencies(output_2);

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

    std::string GccProbe::buildCommandWithIncludes(
        const std::filesystem::path& source,
        const std::filesystem::path& objectFilepath,
        const std::filesystem::path& dependencyFilepath,
        const CompilationUnit* compilationUnit
    ) const
    {
        // Collect project include directories from direct header dependencies
        TransparentUnorderedSet<std::string> includeDirsSet;
        for (const auto& dep : compilationUnit->getSourceFile().directDependencies())
        {
            if (const auto dir = dep.parent_path().lexically_normal().string();
                !dir.empty()
            )
            {
                includeDirsSet.insert(dir);
            }
        }

        auto quote = [](const std::filesystem::path& p)
        {
            // Basic quoting for paths with spaces (Linux/WSL)
            const std::string s = p.string();
            return "'" + s + "'";
        };

        // Build command
        std::string command = std::format(
            "{} -std=gnu++23 -x c++ -fPIC -c {} -o {} -MMD -MP -MF {}",
            quote(findCompiler()),
            quote(source),
            quote(objectFilepath),
            quote(dependencyFilepath)
        );

        // Project include dirs (-I)
        for (const auto& dir : includeDirsSet)
        {
            command = std::format("{} -I '{}'", command, dir);
        }

        // System include dirs (-isystem)
        for (const auto& sysInc : getSystemIncludes())
        {
            command = std::format("{} -isystem {}",command, quote(sysInc));
        }

        return command;
    }

    ObjectFile GccProbe::compile(
        CompilationUnit* compilationUnit,
        const std::filesystem::path& build_directory,
        const bool skipRebuildIfUpToDate
    ) const
    {
        const std::filesystem::path source = compilationUnit->getSourceFile().path();
        const std::filesystem::path object_filepath = build_directory / (source.stem().string() + ".o");
        const std::filesystem::path dependency_filepath = build_directory / (source.stem().string() + ".d");

        if (skipRebuildIfUpToDate)
        {
            if (const auto last_write_time = System::getLastWriteTime(source);
                std::filesystem::exists(object_filepath) &&
                std::filesystem::exists(dependency_filepath) &&
                last_write_time <= System::getLastWriteTime(object_filepath) &&
                last_write_time <= System::getLastWriteTime(dependency_filepath)
            )
            {
                return ObjectFile{object_filepath, dependency_filepath};
            }
        }

        // Ensure output directory exists
        std::error_code ec;
        std::filesystem::create_directories(build_directory, ec);

        std::string command = buildCommandWithIncludes(
            source,
            object_filepath,
            dependency_filepath,
            compilationUnit
        );

        const auto [exit_code, output] = System::ExecuteCommand(command + " 2>&1");

        // Since ExecuteCommandAndCaptureOutput doesn't give us the exit code here,
        // do a quick existence check for the object file to determine success.
        if (!std::filesystem::exists(object_filepath))
        {
            throw faults::failed::Compilation{
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

        if (!std::filesystem::exists(dependency_filepath))
        {
            throw faults::failed::Compilation{
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

        return ObjectFile(object_filepath, dependency_filepath);
    }


    std::string GccProbe::createExecutableLinkCommand(
        const std::span<Linkable*>& linkables,
        const std::filesystem::path& out_path
    )
    {
        std::ostringstream cmd;

        cmd << "g++ -o '" << out_path.string() << "'";

        for (const auto& linkable : linkables)
        {
            if (!linkable->getLinkable().empty())
            {
                cmd << " '" << linkable->getLinkable().string() << "'";
            }
        }

        return cmd.str();
    }

    std::string GccProbe::createSharedLibraryLinkCommand(
        const std::span<Linkable*>& linkables,
        const std::filesystem::path& out_path
    )
    {
        std::ostringstream cmd;

        cmd << "g++ -shared -o '" << out_path.string() << "'";

        for (const auto& linkable : linkables)
        {
            if (!linkable->getLinkable().empty())
            {
                cmd << " '" << linkable->getLinkable().string() << "'";
            }
        }

        return cmd.str();
    }

    std::string GccProbe::createStaticLibraryLinkCommand(
        const std::span<Linkable*>& linkables,
        const std::filesystem::path& out_path
    )
    {
        std::ostringstream cmd;

        cmd << "ar rcs '" << out_path.string() << "'";

        for (const auto& linkable : linkables)
        {
            if (!linkable->getLinkable().empty())
            {
                cmd << " '" << linkable->getLinkable().string() << "'";
            }
        }

        return cmd.str();
    }

    void GccProbe::link(
        const std::span<Linkable*>& linkables,
        const std::filesystem::path& installDirectory,
        const std::string& filename,
        LinkingOutput linkType
    ) const
    {
        if (linkables.empty())
        {
            throw std::invalid_argument("No translation units to link");
        }

        std::error_code ec;
        std::filesystem::create_directories(installDirectory, ec);

        const auto out_path = installDirectory / filename;

        std::string command;

        switch (linkType)
        {
            case LinkingOutput::Executable:
            {
                command = createExecutableLinkCommand(linkables, out_path);
                break;
            }
            case LinkingOutput::SharedLibrary:
            {
                command = createSharedLibraryLinkCommand(linkables, out_path);
                break;
            }
            case LinkingOutput::StaticLibrary:
            {
                command = createStaticLibraryLinkCommand(linkables, out_path);
                break;
            }
            default:
                throw std::invalid_argument("Unknown LinkType");
        }

        logger.print("{}", command);

        const auto [exit_code, output] = System::ExecuteCommand(command + " 2>&1");

        if (!std::filesystem::exists(out_path))
        {
            throw faults::failed::Linking(
                std::format(
                    "Failed to produce output:\nCommand:\n{}\nOutput:\n{}\n",
                    command,
                    output
                )
            );
        }
    }

    bool GccProbe::exists()
    {
        const auto [exit_code, output] = System::ExecuteCommand("g++ -dumpfullversion 2>&1");

        return exit_code == 0;
    }

    std::string GccProbe::version()
    {
        const auto [result, output] = System::ExecuteCommand("g++ -dumpfullversion 2>&1");

        if (result != 0)
        {
            throw faults::failed::CompilerVersionQuery(
                std::format(
                    "Command Execution Failed\nCommand: g++ --version 2>&1\nOutput: {}\n",
                    output
                )
            );
        }

        return output;
    }
}