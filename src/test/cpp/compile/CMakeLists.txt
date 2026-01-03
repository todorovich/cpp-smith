add_executable(test_compile)

add_test(NAME TestCompile COMMAND test_compile)

target_link_libraries(test_compile
    PRIVATE
        cpp-compile
        cpp-test-main
        test_definitions
)

target_sources(test_compile
    PRIVATE
        test_build_system.cpp
        test_compiler_probe.cpp
        test_executable.cpp
        test_shared_library.cpp
        test_static_library.cpp
)

