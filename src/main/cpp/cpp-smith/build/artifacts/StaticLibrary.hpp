#pragma once

#include "Artifact.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace cpp_smith
{
    class StaticLibrary : public Artifact
    {
        std::vector<std::filesystem::path> _sources;

    public:
        StaticLibrary(std::string name, std::vector<std::filesystem::path> sources)
            : Artifact(std::move(name))
            , _sources(std::move(sources))
        {}

        [[nodiscard]] std::vector<std::filesystem::path> sourceFiles() const override
        {
            return _sources;
        }
    };
}

#include "StaticLibraryBuilder.hpp"