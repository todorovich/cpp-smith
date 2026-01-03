add_library(cpp-typeid INTERFACE)

target_sources(cpp-typeid
    INTERFACE
        typeid/TypeId.hpp
        typeid/TypeKey.hpp
        typeid/TypeIdList.hpp
)

target_include_directories(cpp-typeid INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
