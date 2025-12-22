#pragma once

#include "artifacts/ArtifactBuilder.hpp"

#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "artifacts/ArtifactBuilderBase.hpp"

namespace cpp_smith
{
    class Project;

    // Builder specialization for StaticLibrary
    template <>
    class ArtifactBuilder<StaticLibrary> : public ArtifactBuilderBase<StaticLibrary>
    {
        Project& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;

        ArtifactBuilder(Project& parent, std::string name)
            : ArtifactBuilderBase(parent)
            , _parent(parent)
            , _name(std::move(name))
        {}

        [[nodiscard]] std::unique_ptr<StaticLibrary> _create() const override
        {
            return std::make_unique<StaticLibrary>(_name, _sources);
        }

    public:
        friend Project;

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

        [[nodiscard]] std::unique_ptr<Artifact> create() const
        {
            return std::make_unique<StaticLibrary>(_name, _sources);
        }
    };
}
