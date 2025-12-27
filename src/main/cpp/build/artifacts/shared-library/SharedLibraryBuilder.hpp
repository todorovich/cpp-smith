#pragma once

#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/ArtifactBuilderBase.hpp"
#include "Project.hpp"

// ReSharper disable once CppRedundantNamespaceDefinition
namespace cpp_smith
{
    // Builder specialization for SharedLibrary
    template <>
    class ArtifactBuilder<SharedLibrary> : public ArtifactBuilderBase<SharedLibrary>
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

        [[nodiscard]] std::unique_ptr<SharedLibrary> _create() const override
        {
            return std::make_unique<SharedLibrary>(
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
