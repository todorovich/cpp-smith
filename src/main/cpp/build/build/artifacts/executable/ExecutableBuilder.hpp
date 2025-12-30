#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "build/artifacts/executable/Executable.hpp"
#include "build/artifacts/ArtifactBuilder.hpp"
#include "build/artifacts/ArtifactBuilderBase.hpp"
#include "build/Project.hpp"

// ReSharper disable once CppRedundantNamespaceDefinition
namespace cpp_smith
{
    template <>
    class ArtifactBuilder<Executable> : public ArtifactBuilderBase<Executable>
    {
        std::string _name;
        Project& _parent;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        ArtifactBuilder(Project& parent, std::string name)
            : ArtifactBuilderBase(parent)
            , _name(std::move(name))
            , _parent(parent)
        {}

        [[nodiscard]] std::unique_ptr<Executable> _create() const override
        {
            return std::make_unique<Executable>(
                _parent,
                ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
                std::vector<ArtifactCoordinates>{},
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