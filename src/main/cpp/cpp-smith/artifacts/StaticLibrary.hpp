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

        [[nodiscard]] const std::vector<std::filesystem::path>& sources() const override
        {
            return _sources;
        }

        void build(const Configuration* configuration,
                   const std::filesystem::path& build_directory,
                   const std::filesystem::path& install_directory) const override
        {

        }
    };
}

#include "StaticLibraryBuilder.hpp"