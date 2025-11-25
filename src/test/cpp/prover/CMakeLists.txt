add_executable(test_assert)

add_test(NAME TestAssert COMMAND test_assert)

target_link_libraries(test_assert
    PRIVATE
        cpp-smith
        cpp-prover
        test_definitions
)

target_sources(test_assert
    PRIVATE
        test_assert.cpp
)

add_executable(test_ansi)

add_test(NAME TestAnsi COMMAND test_ansi)

target_link_libraries(test_ansi
    PRIVATE
        cpp-smith
        cpp-prover
        test_definitions
)

target_sources(test_ansi
    PRIVATE
        test_ansi.cpp
)