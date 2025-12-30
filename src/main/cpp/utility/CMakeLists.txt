add_library(cpp-containers INTERFACE)

target_sources(cpp-containers
        INTERFACE
        containers/TransparentContainers.hpp
)

target_include_directories(cpp-containers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})