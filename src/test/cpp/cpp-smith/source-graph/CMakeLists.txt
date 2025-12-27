add_executable(test_source_graph)

add_test(NAME SourceGraphTest COMMAND test_source_graph)

target_link_libraries(test_source_graph
    PRIVATE
        cpp-smith
        cpp-test-main
        test_definitions
)

target_sources(test_source_graph
    PRIVATE
        test_source_file.cpp
        test_source_graph.cpp
)
