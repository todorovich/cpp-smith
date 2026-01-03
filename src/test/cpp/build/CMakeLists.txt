add_executable(test_build)

add_test(NAME TestBuild COMMAND test_build)

target_link_libraries(test_build
    PRIVATE
        cpp-build
        cpp-test-main
        test_definitions
)

target_sources(test_build
    PRIVATE
        test_project.cpp

)
