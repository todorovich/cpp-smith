#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "../../../../build/build/artifacts/ArtifactFactory.hpp"
#include "../../../../build/build/Factory.hpp"
#include "../Executable.hpp"

namespace cpp_smith
{
    class ProjectInterface;

    class ExecutableFactory : public ArtifactFactory<Executable>
    {
        std::string _name;
        ProjectInterface& _parent;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        ExecutableFactory(ProjectInterface& parent, std::string name);

        [[nodiscard]] std::unique_ptr<Executable> _create() const override;

    public:
        friend Project;
        friend struct Factory<Executable>;

        ExecutableFactory& addSource(std::filesystem::path source);
        ExecutableFactory& addSources(std::vector<std::filesystem::path> sources);

        ExecutableFactory& addDependency(ArtifactCoordinates coordinates);
        ExecutableFactory& addDependencies(std::vector<ArtifactCoordinates> coordinates);
    };

    template <>
    struct Factory<Executable>
    {
        using factory = ExecutableFactory;

        static factory create(ProjectInterface& project, std::string name)
        {
            return factory{ project, std::move(name) };
        }
    };
}
