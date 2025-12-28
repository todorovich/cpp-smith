add_library(cpp-compile STATIC)

target_link_libraries(cpp-compile
    PUBLIC
        cpp-system
        cpp-containers
)

target_sources(cpp-compile
    PRIVATE
        model/Configuration.cpp
        model/SourceFile.cpp
        compiler-probe/GccProbe.cpp
    PUBLIC
        model/Architecture.hpp
        model/CompilerType.hpp
        model/CompilationUnit.hpp
        model/Configuration.hpp
        model/Linkable.hpp
        model/SourceFile.hpp
        model/Platform.hpp
        compiler-probe/CompilerProbe.hpp
        compiler-probe/GccProbe.hpp
        compiler-probe/ProbeUtils.hpp
        source-graph/SourceGraph.hpp
)

target_include_directories(cpp-compile INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
