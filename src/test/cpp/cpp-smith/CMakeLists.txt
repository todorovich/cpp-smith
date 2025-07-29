add_executable(test_build_environment)

add_test(NAME BuildEnvironmentTest COMMAND test_build_environment)

target_link_libraries(test_build_environment
    PRIVATE
        cpp-smith-lib
        test_definitions
        Catch2::Catch2WithMain
)

target_sources(test_build_environment
    PRIVATE
        test_build_environment.cpp
)

add_subdirectory(compiler-probe)
add_subdirectory(source-graph)
