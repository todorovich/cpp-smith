add_library(cpp-system INTERFACE)

target_sources(cpp-system
    PUBLIC
        PosixPipe.hpp
        PosixSystem.hpp
        System.hpp
)

target_include_directories(cpp-system INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
