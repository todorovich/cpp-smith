add_subdirectory(source-graph)
add_subdirectory(compiler-probe)

add_library(cpp-smith-lib STATIC
        build/Configuration.cpp
        build/Configuration.hpp)

target_sources(cpp-smith-lib
    PRIVATE
        BuildEnvironment.cpp
    PUBLIC
        BuildEnvironment.hpp
        Exceptions.hpp
)

target_link_libraries(cpp-smith-lib
    PUBLIC
        source-graph-lib
)