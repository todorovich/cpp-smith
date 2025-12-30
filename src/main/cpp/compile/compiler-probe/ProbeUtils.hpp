#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <regex>
#include <sstream>
#include <memory>

#include "faults.hpp"
#include "System.hpp"

inline std::vector<std::filesystem::path> ParseSystemIncludeSearchPaths(const std::string& driver_command_for_verbose_includes)
{
    std::vector<std::filesystem::path> include_directories;

    if (auto result = System::ExecuteCommand(driver_command_for_verbose_includes); result.exit_code == 0)
    {
        std::istringstream stream(result.output);
        std::string line;
        auto in_section = false;

        while (std::getline(stream, line))
        {
            if (line.find("#include <...> search starts here:") != std::string::npos)
            {
                in_section = true;
                continue;
            }
            if (line.find("End of search list.") != std::string::npos)
            {
                break;
            }
            if (in_section)
            {
                if (std::string trimmed = std::regex_replace(line, std::regex(R"(^\s+)"), "");

                    !trimmed.empty()
                )
                {
                    include_directories.emplace_back(trimmed);
                }
            }
        }
        return include_directories;
    }
    else
    {
        throw faults::failed::ParseSystemIncludes(
            std::format("Command Execution Failed\nCommand: {} ", driver_command_for_verbose_includes)
        );
    }

}

inline std::vector<std::filesystem::path> ParseMakeStyleDependencies(const std::string& make_style_dependency_text)
{
    std::string s = make_style_dependency_text;
    s = std::regex_replace(s, std::regex("\\\\\n"), " ");

    const auto colon = s.find(':');
    if (colon == std::string::npos) { return {}; }

    const std::string rhs = s.substr(colon + 1);

    std::vector<std::filesystem::path> dependencies;
    std::istringstream is(rhs);
    std::string token;

    while (is >> token)
    {
        if (token == "|" || token == "\\") { continue; }
        dependencies.emplace_back(token);
    }
    return dependencies;
}
