add_library(cpp-compile STATIC)

target_link_libraries(cpp-compile
    PUBLIC
        cpp-log
        cpp-system
        cpp-containers
)

target_sources(cpp-compile
    PRIVATE
        compile/model/Configuration.cpp
        compile/model/SourceFile.cpp
        compile/compiler-probe/GccProbe.cpp
    PUBLIC
        compile/model/Architecture.hpp
        compile/model/CompilerType.hpp
        compile/model/CompilationUnit.hpp
        compile/model/Configuration.hpp
        compile/model/Linkable.hpp
        compile/model/SourceFile.hpp
        compile/model/Platform.hpp
        compile/compiler-probe/CompilerProbe.hpp
        compile/compiler-probe/GccProbe.hpp
        compile/compiler-probe/ProbeUtils.hpp
        compile/source-graph/SourceGraph.hpp
)

target_include_directories(cpp-compile INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
