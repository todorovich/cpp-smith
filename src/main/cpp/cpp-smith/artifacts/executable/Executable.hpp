#pragma once

#include "artifacts/Artifact.hpp"

#include <filesystem>
#include <vector>

namespace cpp_smith
{
    class Configuration;
    class CompilerProbe;

    class Executable final : public Artifact
    {
        std::vector<std::filesystem::path> _sources;

    public:
        Executable(std::string name, std::vector<std::filesystem::path> _sources)
            : Artifact(std::move(name))
            , _sources(std::move(_sources))
        {}

        // Implementation Files that define Translation Units
        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const override
        {
            return _sources;
        }

        void build(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const override;
    };
}

