add_library(cpp-fault INTERFACE)

target_link_libraries(cpp-fault INTERFACE :libstdc++exp.a)

target_sources(cpp-fault
    PUBLIC
        faults/faults.hpp
        faults/Fault.hpp
        faults/failed/Compilation.hpp
        faults/failed/CompilerVersionQuery.hpp
        faults/failed/ParseSystemIncludes.hpp
        faults/failed/FileSystem.hpp
        faults/failed/FileOpen.hpp
        faults/failed/Linking.hpp
        faults/invalid/Argument.hpp
        faults/invalid/CircularDependency.hpp
        faults/missing/Configuration.hpp
        faults/missing/Dependency.hpp
        faults/unsupported/CompilerVersion.hpp
        faults/unsupported/Cast.hpp
        faults/violated/Assertion.hpp
)

target_include_directories(cpp-fault INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
