#include "StaticLibrary.hpp"

#include "../BuildSystem.hpp"

cpp_smith::BuildSystem& cpp_smith::ArtifactBuilder<cpp_smith::StaticLibrary>::buildSystem()
{
    return _parent.addArtifact(build());
}