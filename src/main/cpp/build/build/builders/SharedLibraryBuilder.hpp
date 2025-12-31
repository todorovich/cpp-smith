#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "build/artifacts/shared-library/SharedLibrary.hpp"
#include "build/builders/ArtifactBuilder.hpp"
#include "build/builders/ArtifactBuilderBase.hpp"

namespace cpp_smith
{
    template <>
    class ArtifactBuilder<SharedLibrary> : public ArtifactBuilderBase<SharedLibrary>
    {
        ProjectInterface& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        ArtifactBuilder(ProjectInterface& parent, std::string name);

        [[nodiscard]] std::unique_ptr<SharedLibrary> _create() const override;

    public:
        friend class Project;

        ArtifactBuilder& addSource(std::filesystem::path source);
        ArtifactBuilder& addSources(std::vector<std::filesystem::path> sources);

        ArtifactBuilder& addDependency(ArtifactCoordinates coordinates);
        ArtifactBuilder& addDependencies(std::vector<ArtifactCoordinates> coordinates);
    };
}