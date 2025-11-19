#include "SharedLibrary.hpp"

#include "../Project.hpp"

cpp_smith::Project& cpp_smith::ArtifactBuilder<cpp_smith::SharedLibrary>::submit()
{
    return _parent.accept(create());
}