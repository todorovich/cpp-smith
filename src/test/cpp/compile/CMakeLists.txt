add_executable(test_compiler_probe)

add_test(NAME CompilerProbeTest COMMAND test_compiler_probe)

target_link_libraries(test_compiler_probe
    PRIVATE
        cpp-smith
        cpp-test-main
        test_definitions
)

target_sources(test_compiler_probe
    PRIVATE
        test_compiler_probe.cpp
)

