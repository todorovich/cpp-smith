#pragma once

#include "ArtifactBase.hpp"

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class TestReport : public ArtifactBase
    {
        std::vector<std::filesystem::path> _sources;

    public:
        explicit TestReport(std::string name)
            : ArtifactBase(std::move(name))
        {}

        TestReport& addSources(std::vector<std::filesystem::path> files)
        {
            _sources.insert(_sources.end(), files.begin(), files.end());
            return *this;
        }

        [[nodiscard]] std::vector<std::filesystem::path> sourceFiles() const override
        {
            return _sources;
        }
    };
}
