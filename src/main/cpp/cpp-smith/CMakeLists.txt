add_library(cpp-smith STATIC)

target_include_directories(cpp-smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-smith
    PRIVATE
        Exceptions.hpp
        Project.cpp
        configuration/Configuration.cpp
        configuration/ConfigurationBuilder.cpp
        artifacts/ArtifactBuilder.cpp
        artifacts/Executable.cpp
        artifacts/ExecutableBuilder.cpp
        artifacts/SharedLibraryBuilder.cpp
        artifacts/StaticLibraryBuilder.cpp
        compiler-probe/CompilerProbe.cpp
        compiler-probe/GccProbe.cpp
        source-graph/SourceFile.cpp
        source-graph/SourceGraph.cpp
        source-graph/TranslationUnit.cpp
    PUBLIC
        Project.hpp
        configuration/Configuration.hpp
        configuration/ConfigurationBuilder.hpp
        artifacts/Artifact.hpp
        artifacts/ArtifactBuilder.hpp
        artifacts/Executable.hpp
        artifacts/ExecutableBuilder.hpp
        artifacts/SharedLibrary.hpp
        artifacts/SharedLibraryBuilder.hpp
        artifacts/StaticLibrary.hpp
        artifacts/StaticLibraryBuilder.hpp
        compiler-probe/CompilerProbe.hpp
        compiler-probe/GccProbe.hpp
        source-graph/SourceFile.hpp
        source-graph/SourceGraph.hpp
        source-graph/TranslationUnit.hpp
)