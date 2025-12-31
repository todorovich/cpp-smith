#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "build/Project.hpp"
#include "build/builders/ArtifactBuilder.hpp"
#include "build/builders/ArtifactBuilderBase.hpp"
#include "build/artifacts/executable/Executable.hpp"

namespace cpp_smith
{

    template <>
    class ArtifactBuilder<Executable> : public ArtifactBuilderBase<Executable>
    {
        std::string _name;
        ProjectInterface& _parent;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        ArtifactBuilder(ProjectInterface& parent, std::string name);

        [[nodiscard]] std::unique_ptr<Executable> _create() const override;

    public:
        friend Project;

        ArtifactBuilder& addSource(std::filesystem::path source);
        ArtifactBuilder& addSources(std::vector<std::filesystem::path> sources);

        ArtifactBuilder& addDependency(ArtifactCoordinates coordinates);
        ArtifactBuilder& addDependencies(std::vector<ArtifactCoordinates> coordinates);
    };
}