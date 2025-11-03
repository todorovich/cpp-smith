add_subdirectory(cpp-smith)

add_executable(c++smith)

target_sources(c++smith
    PRIVATE
        main.cpp
)

target_include_directories(c++smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})