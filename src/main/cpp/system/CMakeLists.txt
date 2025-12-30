add_library(cpp-system INTERFACE)

target_link_libraries(cpp-system
    INTERFACE
        cpp-fault
)

target_sources(cpp-system
    PUBLIC
        system/Platform.hpp
        system/PosixPipe.hpp
        system/PosixSystem.hpp
        system/System.hpp
)

target_include_directories(cpp-system INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
