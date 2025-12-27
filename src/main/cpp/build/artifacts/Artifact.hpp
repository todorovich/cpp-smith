#pragma once

#include <filesystem>
#include <vector>
#include <span>
#include <cassert>

#include "ArtifactCoordinates.hpp"
#include "ArtifactType.hpp"
#include "ArtifactTypes.hpp"

namespace cpp_smith
{
    class Project;
    class Configuration;
    class CompilerProbe;

    class Artifact
    {
        ArtifactCoordinates _artifact_coordinates;
        std::vector<ArtifactCoordinates> _dependencies;
        ArtifactTypes _types;

      protected:
        Project& _parent;

        static std::vector<ArtifactType>& addType(ArtifactType&& type, std::vector<ArtifactType>& types)
        {
            types.emplace_back(std::move(type));

            return types;
        }

        static std::vector<ArtifactType>&& addType(ArtifactType&& type, std::vector<ArtifactType>&& types)
        {
            types.emplace_back(std::move(type));

            return std::move(types);
        }

        explicit Artifact(
            Project& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const ArtifactType& type
        );

        explicit Artifact(
            Project& project,
            const ArtifactCoordinates& artifactCoordinate,
            const std::vector<ArtifactCoordinates>& dependencies,
            const ArtifactTypes& types
        );

      public:
        virtual ~Artifact() = default;

        virtual void create(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const = 0;

        [[nodiscard]] const ArtifactCoordinates& getCoordinates() const noexcept { return _artifact_coordinates; }
        [[nodiscard]] const std::vector<ArtifactCoordinates>& getDependencies() const noexcept { return _dependencies; }
        [[nodiscard]] ArtifactTypes getTypes() const noexcept { return _types; }

        [[nodiscard]] bool is(const ArtifactType type) const noexcept
        {
            return _types.contains(type);
        }

        template <class T>
        [[nodiscard]] bool is() const noexcept { return is(ArtifactType::of<T>()); }

        template <class T>
        [[nodiscard]] T& as() & noexcept
        {
            assert(is<T>() && "Artifact::as<T>() called but artifact type does not match");
            return static_cast<T&>(*this);
        }

        template <class T>
        [[nodiscard]] const T& as() const& noexcept
        {
            assert(is<T>() && "Artifact::as<T>() called but artifact type does not match");
            return static_cast<const T&>(*this);
        }
    };
}
