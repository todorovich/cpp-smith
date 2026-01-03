#pragma once

#include <filesystem>
#include <vector>
#include <cassert>

#include "IdentifiedType.hpp"
#include "build/ProjectInterface.hpp"
#include "build/artifacts/ArtifactCoordinates.hpp"
#include "build/artifacts/TypeId.hpp"
#include "build/artifacts/TypeIdList.hpp"

namespace cpp_smith
{
    class Configuration;
    class CompilerProbe;

    class Artifact : public IdentifiedType
    {
        ArtifactCoordinates _artifact_coordinates;
        std::vector<ArtifactCoordinates> _dependencies;


      protected:
        ProjectInterface& _parent;

        /*static std::vector<TypeId>& addType(TypeId&& type, std::vector<TypeId>& types)
        {
            types.emplace_back(std::move(type));

            return types;
        }

        static std::vector<TypeId>&& addType(TypeId&& type, std::vector<TypeId>&& types)
        {
            types.emplace_back(std::move(type));

            return std::move(types);
        }*/

        explicit Artifact(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const TypeId& type
        );

        explicit Artifact(
            ProjectInterface& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const TypeIdList& types
        );

      public:
        virtual ~Artifact() = default;

        virtual void create(
            const Configuration* configuration
        ) const = 0;

        [[nodiscard]] const ArtifactCoordinates& getCoordinates() const noexcept { return _artifact_coordinates; }
        [[nodiscard]] const std::vector<ArtifactCoordinates>& getDependencies() const noexcept { return _dependencies; }

    };
}
