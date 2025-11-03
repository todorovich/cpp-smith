#include "SharedLibrary.hpp"

#include "../BuildSystem.hpp"

cpp_smith::BuildSystem& cpp_smith::ArtifactBuilder<cpp_smith::SharedLibrary>::buildSystem()
{
    return _parent.addArtifact(build());
}