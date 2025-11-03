#include "ExecutableBuilder.hpp"

#include "../BuildSystem.hpp"

[[maybe_unused]] cpp_smith::BuildSystem& cpp_smith::ArtifactBuilder<cpp_smith::Executable>::buildSystem()
{
    return _parent.addArtifact(build());
}