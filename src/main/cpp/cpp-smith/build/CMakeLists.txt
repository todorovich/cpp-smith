add_library(build-system STATIC)

target_sources(build-system
    PRIVATE
        BuildSystem.cpp
        Configuration.cpp
        ConfigurationBuilder.cpp
        artifacts/ArtifactBuilder.cpp
        artifacts/ExecutableBuilder.cpp
        artifacts/SharedLibraryBuilder.cpp
        artifacts/StaticLibraryBuilder.cpp
    PUBLIC
        BuildSystem.hpp
        Configuration.hpp
        ConfigurationBuilder.hpp
        artifacts/Artifact.hpp
        artifacts/ArtifactBuilder.hpp
        artifacts/Executable.hpp
        artifacts/ExecutableBuilder.hpp
        artifacts/SharedLibrary.hpp
        artifacts/SharedLibraryBuilder.hpp
        artifacts/StaticLibrary.hpp
        artifacts/StaticLibraryBuilder.hpp
)

target_include_directories(build-system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
