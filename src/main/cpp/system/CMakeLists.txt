add_library(cpp-system INTERFACE)

target_link_libraries(cpp-system
    INTERFACE
        cpp-fault
)

target_sources(cpp-system
    PUBLIC
        Platform.hpp
        PosixPipe.hpp
        PosixSystem.hpp
        System.hpp
)

target_include_directories(cpp-system INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
