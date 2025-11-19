#include "ExecutableBuilder.hpp"

#include "../Project.hpp"

[[maybe_unused]] cpp_smith::Project& cpp_smith::ArtifactBuilder<cpp_smith::Executable>::submit()
{
    return _parent.accept(create());
}