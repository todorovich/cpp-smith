#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "../SharedLibrary.hpp"
#include "../../../../build/build/artifacts/ArtifactFactory.hpp"
#include "../../../../build/build/Factory.hpp"

namespace cpp_smith
{
    class ProjectInterface;

    class SharedLibraryFactory : public ArtifactFactory<SharedLibrary>
    {
        ProjectInterface& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        SharedLibraryFactory(ProjectInterface& parent, std::string name);

        [[nodiscard]] std::unique_ptr<SharedLibrary> _create() const override;

    public:
        friend struct Factory<SharedLibrary>;

        SharedLibraryFactory& addSource(std::filesystem::path source);
        SharedLibraryFactory& addSources(std::vector<std::filesystem::path> sources);

        SharedLibraryFactory& addDependency(ArtifactCoordinates coordinates);
        SharedLibraryFactory& addDependencies(std::vector<ArtifactCoordinates> coordinates);
    };

    template <>
    struct Factory<SharedLibrary>
    {
        using factory = SharedLibraryFactory;

        static factory create(ProjectInterface& project, std::string name)
        {
            return factory{ project, std::move(name) };
        }
    };
}