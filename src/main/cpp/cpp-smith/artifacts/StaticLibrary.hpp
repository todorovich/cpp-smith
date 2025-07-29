#pragma once

#include "ArtifactBase.hpp"

class StaticLibrary : public cpp_smith::ArtifactBase
{
    std::vector<std::filesystem::path> _sources;

public:
    StaticLibrary& addSources(std::vector<std::filesystem::path> files)
    {
        _sources.insert(_sources.end(), files.begin(), files.end());
        return *this;
    }

    std::vector<std::filesystem::path> sourceFiles() const override
    {
        return _sources;
    }
};

