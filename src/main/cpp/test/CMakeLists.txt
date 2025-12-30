add_library(cpp-test STATIC)

target_include_directories(cpp-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-test
    PRIVATE
        test/Tester.cpp
    PUBLIC
        test/Ansi.hpp
        test/Assert.hpp
        test/Diff.hpp
        test/Tester.hpp
        test/Test.hpp
        test/TestInterface.hpp
        test/TestRegistry.hpp
        test/TestResult.hpp
)

target_link_libraries(cpp-test
    PUBLIC
        cpp-fault
        cpp-log
        cpp-containers
)

add_library(cpp-test-main STATIC)

target_include_directories(cpp-test-main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-test-main
    PRIVATE
        test/main.cpp
)

target_link_libraries(cpp-test-main
    PUBLIC
        cpp-test
)
