#pragma once

#include "Artifact.hpp"

#include <concepts>

namespace cpp_smith
{
    class Project;

    template <typename T>
    concept ArtifactType = std::derived_from<T, Artifact>;

    // Primary template. Specializations are provided per artifact type.
    template <ArtifactType T> class ArtifactBuilder
    {
        Project& _buildSystem;

      public:
        explicit ArtifactBuilder(Project& buildSystem);

        virtual ~ArtifactBuilder() = default;

        virtual std::unique_ptr<T> create() const = 0;

        Project& submit();
    };

} // namespace cpp_smith
