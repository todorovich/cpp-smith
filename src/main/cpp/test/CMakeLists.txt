add_library(cpp-test STATIC)

target_include_directories(cpp-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-test
    PRIVATE
        Tester.cpp
    PUBLIC
        Ansi.hpp
        Assert.hpp
        Diff.hpp
        Tester.hpp
        Test.hpp
        TestInterface.hpp
        TestRegistry.hpp
        TestResult.hpp
)

target_link_libraries(cpp-test
    PUBLIC
        cpp-fault
        cpp-log
)

add_library(cpp-test-main STATIC)

target_include_directories(cpp-test-main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-test-main
    PRIVATE
        main.cpp
)

target_link_libraries(cpp-test-main
    PUBLIC
        cpp-test
)
