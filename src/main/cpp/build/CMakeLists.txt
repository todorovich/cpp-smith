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
        build/artifacts/executable/Executable.cpp
        build/configuration/ConfigurationBuilder.cpp
    PUBLIC
        build/Configuration.hpp
        build/Project.hpp
        build/ProjectCoordinates.hpp
        build/configuration/ConfigurationBuilder.hpp
        build/artifacts/Artifact.hpp
        build/artifacts/ArtifactBuilder.hpp
        build/artifacts/ArtifactBuilderBase.hpp
        build/artifacts/ArtifactCoordinates.hpp
        build/artifacts/ArtifactType.hpp
        build/artifacts/ArtifactTypes.hpp
        build/artifacts/Executable.hpp
        build/artifacts/executable/Executable.hpp
        build/artifacts/executable/ExecutableBuilder.hpp
        build/artifacts/SharedLibrary.hpp
        build/artifacts/shared-library/SharedLibrary.hpp
        build/artifacts/shared-library/SharedLibraryBuilder.hpp
        build/artifacts/StaticLibrary.hpp
        build/artifacts/static-library/StaticLibrary.hpp
        build/artifacts/static-library/StaticLibraryBuilder.hpp
)
