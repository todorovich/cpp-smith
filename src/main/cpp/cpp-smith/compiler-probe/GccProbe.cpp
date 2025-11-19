#include "GccProbe.hpp"

#include "source-graph/TranslationUnit.hpp"

#include <print>

namespace cpp_smith
{
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
            std::string s = p.string();
            return "'" + s + "'";
        };

        // Collect project include directories from direct header dependencies
        std::unordered_set<std::string> includeDirsSet;
        for (const auto& dep : translationUnit->getSourceFile().directDependencies())
        {
            const auto dir = dep.parent_path().lexically_normal().string();
            if (!dir.empty())
                includeDirsSet.insert(dir);
        }

        // Build command
        std::ostringstream cmd;
        cmd << quote(findCompiler()) << " -std=gnu++23 -x c++ -c " << quote(source) << " -o "
            << quote(object_filepath)
            // Generate dependency file alongside the object
            << " -MMD -MP -MF " << quote(dependency_filepath);

        // Project include dirs (-I)
        for (const auto& dir : includeDirsSet)
        {
            cmd << " -I " << "'" << dir << "'";
        }

        // System include dirs (-isystem)
        for (const auto& sysInc : getSystemIncludes())
        {
            cmd << " -isystem " << quote(sysInc);
        }

        // Execute and capture output
        const std::string fullCmd = cmd.str();
        const std::string output = ExecuteCommandAndCaptureOutput(fullCmd + " 2>&1");

        // Since ExecuteCommandAndCaptureOutput doesn't give us the exit code here,
        // do a quick existence check for the object file to determine success.
        if (!fs::exists(object_filepath))
        {
            throw std::runtime_error("Failed to compile translation unit:"
                                     "\nCommand:\n" +
                                     fullCmd + "\nOutput:\n" + output);
        }

        if (!fs::exists(dependency_filepath))
        {
            throw std::runtime_error("Failed to compile translation unit [no dependency file]:"
                                     "\nCommand:\n" +
                                     fullCmd + "\nOutput:\n" + output);
        }

        translationUnit->setObjectFile(object_filepath);
        translationUnit->setDependencyFile(dependency_filepath);
    }

    void GccProbe::link(
        const std::vector<TranslationUnit*>& translation_units,
        const std::filesystem::path& install_directory,
        const std::string& filename
    ) const
    {
        // TODO: check that all TU's share the same config?
        if (translation_units.empty())
        {
            throw std::runtime_error("No translation units to link");
        }

        // Ensure output directory exists
        std::error_code ec;
        fs::create_directories(install_directory, ec);

        std::ostringstream cmd;
        cmd << "g++ -o '" << install_directory.string() << '/' << filename << "'";

        for (const auto* unit : translation_units)
        {
            if (!unit->getObjectFile().empty())
            {
                cmd << " '" << unit->getObjectFile().string() << "'";
            }
        }

        const std::string command = cmd.str();

        std::println("{}", command);

        const std::string output = ExecuteCommandAndCaptureOutput(command + " 2>&1");

        if (!std::filesystem::exists(install_directory/filename))
        {
            throw std::runtime_error(
                "Failed to link executable:\n"
                "Command:\n" + command + "\n"
                "Output:\n" + output
            );
        }
    }
} // namespace cpp_smith