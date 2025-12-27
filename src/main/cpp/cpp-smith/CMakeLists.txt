add_library(cpp-smith STATIC)

target_link_libraries(cpp-smith
    PUBLIC
        exceptions
)

target_include_directories(cpp-smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-smith
    PRIVATE
        Project.cpp
        configuration/Configuration.cpp
        configuration/ConfigurationBuilder.cpp
        artifacts/executable/Executable.cpp
        compiler-probe/CompilerProbe.cpp
        compiler-probe/GccProbe.cpp
        source-graph/SourceFile.cpp
    PUBLIC
        Configuration.hpp
        Platform.hpp
        Project.hpp
        ProjectCoordinates.hpp
        configuration/Architecture.hpp
        configuration/CompilerType.hpp
        configuration/Configuration.hpp
        configuration/ConfigurationBuilder.hpp
        configuration/Platform.hpp
        artifacts/Artifact.hpp
        artifacts/ArtifactBuilder.hpp
        artifacts/ArtifactBuilderBase.hpp
        artifacts/ArtifactCoordinates.hpp
        artifacts/Executable.hpp
        artifacts/executable/Executable.hpp
        artifacts/executable/ExecutableBuilder.hpp
        artifacts/SharedLibrary.hpp
        artifacts/shared-library/SharedLibrary.hpp
        artifacts/shared-library/SharedLibraryBuilder.hpp
        artifacts/StaticLibrary.hpp
        artifacts/static-library/StaticLibrary.hpp
        artifacts/static-library/StaticLibraryBuilder.hpp
        compiler-probe/CompilerProbe.hpp
        compiler-probe/GccProbe.hpp
        source-graph/Linkable.hpp
        source-graph/SourceFile.hpp
        source-graph/SourceGraph.hpp
        source-graph/CompilationUnit.hpp
        system/System.hpp
        system/PosixPipe.hpp
        system/PosixSystem.hpp
)