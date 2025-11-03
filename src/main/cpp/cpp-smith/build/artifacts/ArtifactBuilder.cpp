#include "ArtifactBuilder.hpp"

#include "../BuildSystem.hpp"

namespace cpp_smith
{
    template <ArtifactType T> ArtifactBuilder<T>::ArtifactBuilder(BuildSystem& buildSystem)
        : _buildSystem{buildSystem}
    {}

    template <ArtifactType T> BuildSystem& ArtifactBuilder<T>::buildSystem()
    {
        return _buildSystem.add(build());
    }

} // namespace cpp_smith
