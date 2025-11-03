add_library(compiler-probe-lib STATIC)

target_sources(compiler-probe-lib
    PRIVATE
        CompilerProbe.cpp
    PUBLIC
        CompilerProbe.hpp
)

target_include_directories(compiler-probe-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})