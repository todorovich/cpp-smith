add_executable(test_typeid)

add_test(NAME TestTypeId COMMAND test_typeid)

target_link_libraries(test_typeid
    PRIVATE
        cpp-compile
        cpp-test-main
        test_definitions
)

target_sources(test_typeid
    PRIVATE
        test_artifact_type.cpp
        test_artifact_types.cpp
)
