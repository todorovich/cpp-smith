#include "BuildEnvironment.hpp"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace cpp_smith
{
    BuildEnvironment::BuildEnvironment(
        std::filesystem::path compiler,
        std::vector<std::string> flags,
        std::vector<std::string> defines,
        std::vector<std::filesystem::path> include_dirs
    )
        : _compiler(std::move(compiler))
        , _flags(std::move(flags))
        , _defines(std::move(defines))
        , _include_dirs(std::move(include_dirs))
    {}

    const std::filesystem::path& BuildEnvironment::compiler() const
    {
        return _compiler;
    }

    std::vector<std::string> BuildEnvironment::_buildCommandArgs(
        const std::filesystem::path& source_file
    ) const
    {
        std::vector<std::string> args = {
            _compiler.string(),
            "-std=c++23",
            "-M", "-MG",
            "-MT", "dummy"
        };

        for (const auto& def : _defines)
        {
            args.push_back("-D" + def);
        }

        for (const auto& dir : _include_dirs)
        {
            args.push_back("-I" + dir.string());
        }

        for (const auto& flag : _flags)
        {
            args.push_back(flag);
        }

        args.push_back(source_file.string());
        return args;
    }

    std::string BuildEnvironment::_joinCommandArgs(
        const std::vector<std::string>& args
    ) const
    {
        std::string command;
        for (const auto& arg : args)
        {
            command += arg + " ";
        }
        return command;
    }

    std::vector<std::filesystem::path> BuildEnvironment::_parseMakefileDeps(
        FILE* pipe
    ) const
    {
        std::vector<std::filesystem::path> deps;
        char buffer[4096];
        bool skip_target = true;

        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            std::string_view view(buffer);
            std::size_t start = 0;

            while (start < view.size())
            {
                std::size_t end = view.find_first_of(" \n\\", start);
                if (end == std::string_view::npos) end = view.size();

                std::string_view token = view.substr(start, end - start);
                start = view.find_first_not_of(" \n\\", end);

                if (skip_target)
                {
                    if (token.ends_with(":"))
                    {
                        skip_target = false;
                    }
                    continue;
                }

                if (!token.empty())
                {
                    deps.emplace_back(token);
                }
            }
        }

        return deps;
    }

    std::vector<std::filesystem::path> BuildEnvironment::resolveDependenciesFor(
        const std::filesystem::path& source_file
    ) const
    {
        auto args = _buildCommandArgs(source_file);
        auto command = _joinCommandArgs(args);

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) return {};

        return _parseMakefileDeps(pipe.get());
    }
}
