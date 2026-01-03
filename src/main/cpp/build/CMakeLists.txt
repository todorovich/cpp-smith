add_library(cpp-build STATIC)

target_link_libraries(cpp-build
    PUBLIC
        cpp-fault
        cpp-system
        cpp-log
        cpp-containers
        cpp-test
)

target_include_directories(cpp-build PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-build
    PRIVATE
        build/Project.cpp
        build/artifacts/Artifact.cpp

    PUBLIC
        build/artifacts/Artifact.hpp
        build/artifacts/ArtifactFactory.hpp
        build/artifacts/ArtifactCoordinates.hpp
        build/artifacts/TypeId.hpp
        build/artifacts/TypeIdList.hpp
        build/Project.hpp
        build/ProjectCoordinates.hpp
        build/ProjectInterface.hpp
        build/Factory.hpp
)
