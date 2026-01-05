add_library(cpp-algorithm INTERFACE)

target_include_directories(cpp-algorithm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cpp-algorithm
    INTERFACE
        cpp-fault
)

target_sources(cpp-algorithm
    PUBLIC
        algorithm/TopologicalSort.hpp
        algorithm/DependencyGraph.hpp
)

