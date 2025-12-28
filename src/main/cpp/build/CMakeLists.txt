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
        Project.cpp
        artifacts/Artifact.cpp
        artifacts/executable/Executable.cpp
        configuration/ConfigurationBuilder.cpp
    PUBLIC
        Configuration.hpp
        Project.hpp
        ProjectCoordinates.hpp
        configuration/ConfigurationBuilder.hpp
        artifacts/Artifact.hpp
        artifacts/ArtifactBuilder.hpp
        artifacts/ArtifactBuilderBase.hpp
        artifacts/ArtifactCoordinates.hpp
        artifacts/ArtifactType.hpp
        artifacts/ArtifactTypes.hpp
        artifacts/Executable.hpp
        artifacts/executable/Executable.hpp
        artifacts/executable/ExecutableBuilder.hpp
        artifacts/SharedLibrary.hpp
        artifacts/shared-library/SharedLibrary.hpp
        artifacts/shared-library/SharedLibraryBuilder.hpp
        artifacts/StaticLibrary.hpp
        artifacts/static-library/StaticLibrary.hpp
        artifacts/static-library/StaticLibraryBuilder.hpp
)
