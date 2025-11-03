#pragma once

#include "ArtifactBuilder.hpp"
#include "StaticLibrary.hpp"

#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace cpp_smith
{
    // Builder specialization for StaticLibrary
    template <>
    class ArtifactBuilder<StaticLibrary>
    {
        BuildSystem& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;

    public:
        ArtifactBuilder(BuildSystem& parent, std::string name)
            : _parent(parent)
            , _name(std::move(name))
        {}

        ArtifactBuilder& addSource(std::filesystem::path source)
        {
            _sources.emplace_back(std::move(source));
            return *this;
        }

        ArtifactBuilder& addSources(std::vector<std::filesystem::path> sources)
        {
            _sources.insert(
                _sources.end(),
                std::make_move_iterator(sources.begin()),
                std::make_move_iterator(sources.end())
            );

            return *this;
        }

        [[nodiscard]] std::unique_ptr<Artifact> build() const
        {
            return std::make_unique<StaticLibrary>(_name, _sources);
        }

        [[maybe_unused]] BuildSystem& buildSystem();
    };
}
