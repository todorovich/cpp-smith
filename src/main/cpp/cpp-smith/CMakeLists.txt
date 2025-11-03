add_subdirectory(build)
add_subdirectory(source-graph)
add_subdirectory(compiler-probe)

add_library(cpp-smith STATIC)

target_sources(cpp-smith
    PUBLIC
        Exceptions.hpp
)

target_link_libraries(cpp-smith
    PUBLIC
        build-system
        source-graph-lib
)

target_include_directories(cpp-smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})