#include "StaticLibrary.hpp"

#include "Project.hpp"

cpp_smith::Project& cpp_smith::ArtifactBuilder<cpp_smith::StaticLibrary>::submit()
{
    return _parent.accept(create());
}