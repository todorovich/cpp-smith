add_subdirectory(exceptions)
add_subdirectory(logging)
add_subdirectory(cpp-smith)
add_subdirectory(test)

add_executable(c++smith)

target_sources(c++smith
    PRIVATE
        cli-main.cpp
)

target_include_directories(c++smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})