add_subdirectory(compiler-probe)
add_subdirectory(source-graph)
add_subdirectory(build-system)

add_executable(test_cpp_smith)

add_test(NAME TestCppSmith COMMAND test_cpp_smith)

target_link_libraries(test_cpp_smith
    PRIVATE
        cpp-smith
        test_definitions
        Catch2::Catch2WithMain
)

target_sources(test_cpp_smith
    PRIVATE
        test_cpp_smith.cpp
)