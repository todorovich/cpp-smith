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
        artifacts/ArtifactBuilder.cpp
        artifacts/executable/Executable.cpp
        artifacts/executable/ExecutableBuilder.cpp
        artifacts/shared-library/SharedLibraryBuilder.cpp
        artifacts/static-library/StaticLibraryBuilder.cpp
        compiler-probe/CompilerProbe.cpp
        compiler-probe/GccProbe.cpp
        source-graph/SourceFile.cpp
        source-graph/SourceGraph.cpp
        source-graph/TranslationUnit.cpp
    PUBLIC
        Platform.hpp
        Project.hpp
        Configuration.hpp
        configuration/Architecture.hpp
        configuration/CompilerType.hpp
        configuration/Configuration.hpp
        configuration/ConfigurationBuilder.hpp
        configuration/Platform.hpp
        artifacts/Artifact.hpp
        artifacts/ArtifactBuilder.hpp
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
        source-graph/SourceFile.hpp
        source-graph/SourceGraph.hpp
        source-graph/TranslationUnit.hpp
)