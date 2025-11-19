#include "ArtifactBuilder.hpp"

#include "Project.hpp"

namespace cpp_smith
{
    template <ArtifactType T> ArtifactBuilder<T>::ArtifactBuilder(Project& buildSystem)
        : _buildSystem{buildSystem}
    {}

    template <ArtifactType T> Project& ArtifactBuilder<T>::submit()
    {
        return _buildSystem.accept(create());
    }

} // namespace cpp_smith
