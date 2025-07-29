add_library(cpp-smith-artifacts STATIC)

target_sources(cpp-smith-artifacts
    PUBLIC
        ArtifactBase.hpp
        Executable.hpp
        SharedLibrary.hpp
        StaticLibrary.hpp
)