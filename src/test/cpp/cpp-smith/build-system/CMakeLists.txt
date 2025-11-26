add_executable(test_build_system)

add_test(NAME TestBuildSystem COMMAND test_build_system)

target_link_libraries(test_build_system
    PRIVATE
        cpp-smith
        cpp-prover-main
        test_definitions
)

target_sources(test_build_system
    PRIVATE
        test_build_system.cpp
        test_executable.cpp
)
