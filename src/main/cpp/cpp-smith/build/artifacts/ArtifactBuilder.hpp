#pragma once

#include "Artifact.hpp"

#include <concepts>

namespace cpp_smith
{
    class BuildSystem;

    template <typename T>
    concept ArtifactType = std::derived_from<T, Artifact>;

    // Primary template. Specializations are provided per artifact type.
    template <ArtifactType T> class ArtifactBuilder
    {
        BuildSystem& _buildSystem;

      public:
        explicit ArtifactBuilder(BuildSystem& buildSystem);

        virtual ~ArtifactBuilder() = default;

        virtual std::unique_ptr<T> build() const = 0;

        BuildSystem& buildSystem();
    };

} // namespace cpp_smith
