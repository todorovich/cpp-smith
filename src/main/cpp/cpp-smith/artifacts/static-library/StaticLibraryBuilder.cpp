#include "artifacts/StaticLibrary.hpp"

#include "Project.hpp"

namespace cpp_smith
{
    // ReSharper disable once CppMemberFunctionMayBeConst
    Project& ArtifactBuilder<StaticLibrary>::submit()
    {
        return _parent.accept(create());
    }
}
