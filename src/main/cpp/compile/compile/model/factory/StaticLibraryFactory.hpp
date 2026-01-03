#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "../StaticLibrary.hpp"
#include "../../../../build/build/artifacts/ArtifactFactory.hpp"
#include "../../../../build/build/Factory.hpp"

namespace cpp_smith
{
    class ProjectInterface;

    class StaticLibraryFactory : public ArtifactFactory<StaticLibrary>
    {
        ProjectInterface& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;
        std::vector<ArtifactCoordinates> _dependencies;

        StaticLibraryFactory(ProjectInterface& parent, std::string name);

        [[nodiscard]] std::unique_ptr<StaticLibrary> _create() const override;

    public:
        friend class  Factory<StaticLibrary>;

        StaticLibraryFactory& addSource(std::filesystem::path source);
        StaticLibraryFactory& addSources(std::vector<std::filesystem::path> sources);

        StaticLibraryFactory& addDependency(ArtifactCoordinates coordinates);
        StaticLibraryFactory& addDependencies(std::vector<ArtifactCoordinates> coordinates);
    };

    template <>
    struct Factory<StaticLibrary>
    {
        using factory = StaticLibraryFactory;

        static factory create(ProjectInterface& project, std::string name)
        {
            return factory{ project, std::move(name) };
        }
    };
}