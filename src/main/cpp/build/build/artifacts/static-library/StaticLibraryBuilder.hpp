#pragma once

#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "build/artifacts/ArtifactBuilder.hpp"
#include "build/artifacts/ArtifactBuilderBase.hpp"

namespace cpp_smith
{
    class Project;

    template <>
    class ArtifactBuilder<StaticLibrary> : public ArtifactBuilderBase<StaticLibrary>
    {
        Project& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        ArtifactBuilder(Project& parent, std::string name)
            : ArtifactBuilderBase(parent)
            , _parent(parent)
            , _name(std::move(name))
        {}

        [[nodiscard]] std::unique_ptr<StaticLibrary> _create() const override
        {
            return std::make_unique<StaticLibrary>(
                _parent,
                ArtifactCoordinates{_parent.getProjectCoordinates(), _name},
                _dependencies,
                _sources
            );
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

        ArtifactBuilder& addDependency(ArtifactCoordinates coordinates)
        {
            _dependencies.emplace_back(std::move(coordinates));

            return *this;
        }

        ArtifactBuilder& addDependencies(std::vector<ArtifactCoordinates> coordinates)
        {
            _dependencies.insert(
                _dependencies.end(),
                std::make_move_iterator(coordinates.begin()),
                std::make_move_iterator(coordinates.end())
            );

            return *this;
        }
    };
}
