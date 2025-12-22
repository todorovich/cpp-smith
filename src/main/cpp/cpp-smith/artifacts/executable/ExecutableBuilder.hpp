#pragma once

#include "Project.hpp"
#include "artifacts/ArtifactBuilder.hpp"
#include "Executable.hpp"

#include <filesystem>
#include <memory>
#include <string>

#include "artifacts/ArtifactBuilderBase.hpp"

// ReSharper disable once CppRedundantNamespaceDefinition
namespace cpp_smith
{
    template <>
    class ArtifactBuilder<Executable> : public ArtifactBuilderBase<Executable>
    {
        std::string _name;
        std::vector<std::filesystem::path> _sources;

        ArtifactBuilder(Project& parent, std::string name)
            : ArtifactBuilderBase(parent)
            , _name(std::move(name))
        {}

        [[nodiscard]] std::unique_ptr<Executable> _create() const override
        {
            return std::make_unique<Executable>(_name, _sources);
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