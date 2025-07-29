add_library(compiler-probe-lib STATIC)

target_sources(compiler-probe-lib
    PRIVATE
        CompilerProbe.cpp
    PUBLIC
        CompilerProbe.hpp
)