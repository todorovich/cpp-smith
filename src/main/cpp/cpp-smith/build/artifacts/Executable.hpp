#pragma once

#include "Artifact.hpp"

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class Executable : public Artifact
    {
        std::filesystem::path _entry_point;

    public:
        Executable(std::string name, std::filesystem::path entry_point)
            : Artifact(std::move(name))
            , _entry_point(std::move(entry_point))
        {}

        [[nodiscard]] const std::filesystem::path& entryPoint() const
        {
            return _entry_point;
        }

        [[nodiscard]] std::vector<std::filesystem::path> sourceFiles() const override
        {
            return { _entry_point };
        }
    };
}

#include "ExecutableBuilder.hpp"