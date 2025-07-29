add_executable(test_compiler_probe)

add_test(NAME CompilerProbeTest COMMAND test_source_graph)

target_link_libraries(test_compiler_probe
    PRIVATE
        test_definitions
        Catch2::Catch2WithMain
)

target_sources(test_compiler_probe
    PRIVATE
        test_compiler_probe.cpp
)

