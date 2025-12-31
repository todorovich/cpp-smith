add_executable(test_cpp_smith)

add_test(NAME TestCppSmith COMMAND test_cpp_smith)

target_link_libraries(test_cpp_smith
    PRIVATE
        cpp-smith
        cpp-test-main
        test_definitions
)

target_sources(test_cpp_smith
    PRIVATE
        test_artifact_type.cpp
        test_artifact_types.cpp
        test_build_system.cpp
        test_cpp_smith.cpp
        test_executable.cpp
        test_project.cpp
)
