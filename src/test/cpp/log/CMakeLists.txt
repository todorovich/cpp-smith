add_executable(test_logger)

add_test(NAME TestLogger COMMAND test_logger)

target_link_libraries(test_logger
    PRIVATE
        cpp-log
        cpp-test-main
        test_definitions
)

target_sources(test_logger
    PRIVATE
        test_logger.cpp
)
