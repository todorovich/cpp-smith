add_subdirectory(utility)
add_subdirectory(faults)
add_subdirectory(log)
add_subdirectory(system)
add_subdirectory(test)
add_subdirectory(compile)
add_subdirectory(build)

add_executable(c++smith)

target_sources(c++smith
    PRIVATE
        cli-main.cpp
)

target_include_directories(c++smith PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})