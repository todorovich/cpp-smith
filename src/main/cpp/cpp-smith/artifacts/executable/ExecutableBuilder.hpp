#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/ArtifactBuilderBase.hpp"
#include "Executable.hpp"
#include "Project.hpp"

// ReSharper disable once CppRedundantNamespaceDefinition
namespace cpp_smith
{
    template <>
    class ArtifactBuilder<Executable> : public ArtifactBuilderBase<Executable>
    {
        std::string _name;
        Project& _parent;
        std::vector<std::filesystem::path> _sources;

        ArtifactBuilder(Project& parent, std::string name)
            : ArtifactBuilderBase(parent)
            , _name(std::move(name))
            , _parent(parent)
        {}

        [[nodiscard]] std::unique_ptr<Executable> _create() const override
        {
            return std::make_unique<Executable>(
                ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
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
    };
}