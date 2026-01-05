add_executable(test_algorithm)

add_test(NAME TestAlgorithm COMMAND test_algorithm)

target_link_libraries(test_algorithm
    PRIVATE
        cpp-algorithm
        cpp-test-main
        test_definitions
)

target_sources(test_algorithm
    PRIVATE
        test_topological_sort.cpp
)
