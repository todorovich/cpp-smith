add_library(cpp-smith STATIC)

target_link_libraries(cpp-smith
    PUBLIC
        cpp-fault
        cpp-system
        cpp-compile
        cpp-log
)

target_include_directories(cpp-smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-smith
    PRIVATE
        build/Project.cpp
        build/artifacts/Artifact.cpp
        build/builders/ConfigurationBuilder.cpp
        build/builders/ExecutableBuilder.cpp
        build/builders/SharedLibraryBuilder.cpp
        build/builders/StaticLibraryBuilder.cpp
        build/artifacts/executable/Executable.cpp
        build/artifacts/shared-library/SharedLibrary.cpp
        build/artifacts/static-library/StaticLibrary.cpp
    PUBLIC
        build/Project.hpp
        build/ProjectCoordinates.hpp
        build/ProjectInterface.hpp
        build/builders/ConfigurationBuilder.hpp
        build/artifacts/Artifact.hpp
        build/builders/ArtifactBuilder.hpp
        build/builders/ArtifactBuilderBase.hpp
        build/artifacts/ArtifactCoordinates.hpp
        build/artifacts/ArtifactType.hpp
        build/artifacts/ArtifactTypes.hpp
        build/artifacts/executable/Executable.hpp
        build/builders/ExecutableBuilder.hpp
        build/artifacts/shared-library/SharedLibrary.hpp
        build/builders/SharedLibraryBuilder.hpp
        build/artifacts/static-library/StaticLibrary.hpp
        build/builders/StaticLibraryBuilder.hpp
)
