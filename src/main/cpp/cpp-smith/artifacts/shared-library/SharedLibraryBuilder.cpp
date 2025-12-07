#include "artifacts/SharedLibrary.hpp"

#include "Project.hpp"

namespace cpp_smith
{
    // ReSharper disable once CppMemberFunctionMayBeConst
    Project& ArtifactBuilder<SharedLibrary>::submit()
    {
        return _parent.accept(create());
    }
}
