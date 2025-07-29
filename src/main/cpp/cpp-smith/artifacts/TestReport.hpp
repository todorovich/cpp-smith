#pragma once

#include "ArtifactBase.hpp"

namespace cpp_smith
{
    class TestReport : public ArtifactBase
    {
        std::vector<std::filesystem::path> _sources;

    public:
        TestReport& addSources(std::vector<std::filesystem::path> files)
        {
            _sources.insert(_sources.end(), files.begin(), files.end());
            return *this;
        }

        std::vector<std::filesystem::path> sourceFiles() const override
        {
            return _sources;
        }
    };
}