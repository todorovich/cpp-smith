#pragma once

#include "ArtifactBase.hpp"

#include <filesystem>

namespace cpp_smith
{
    class Executable : public ArtifactBase
    {
        std::filesystem::path _entry_point;
        std::vector<std::filesystem::path> _source_files;

    public:
        Executable& entryPoint(std::filesystem::path path)
        {
            _entry_point = std::move(path);
            return *this;
        }

        std::vector<std::filesystem::path> sourceFiles() const override
        {
            return { _entry_point };
        }
    };
}
