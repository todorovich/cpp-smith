add_executable(test_build_system)

add_test(NAME TestBuildSystem COMMAND test_build_system)

target_link_libraries(test_build_system
    PRIVATE
        cpp-smith
        test_definitions
        Catch2::Catch2WithMain
)

target_sources(test_build_system
    PRIVATE
        test_build_system.cpp
)
