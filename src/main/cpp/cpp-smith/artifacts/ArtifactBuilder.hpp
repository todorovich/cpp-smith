#pragma once

#include "Artifact.hpp"

#include <concepts>

namespace cpp_smith
{
    template <typename T>
    concept ArtifactType = std::derived_from<T, Artifact>;

    template <ArtifactType T> class ArtifactBuilder;
}
