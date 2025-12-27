#pragma once

#include <concepts>

#include "Artifact.hpp"

namespace cpp_smith
{
    template <typename T>
    concept ArtifactTypeConcept = std::derived_from<T, ::cpp_smith::Artifact>;

    template <ArtifactTypeConcept T> class ArtifactBuilder;
}
