add_library(cpp-prover STATIC)

target_include_directories(cpp-prover PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-prover
    PRIVATE
        Prover.cpp
    PUBLIC
        Ansi.hpp
        Assert.hpp
        Diff.hpp
        Prover.hpp
        Test.hpp
        TestInterface.hpp
        TestRegistry.hpp
        TestResult.hpp
)

target_link_libraries(cpp-prover
    PUBLIC
        exceptions
        logging
)

add_library(cpp-prover-main STATIC)

target_include_directories(cpp-prover-main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-prover-main
    PRIVATE
        prover_main.cpp
)

target_link_libraries(cpp-prover-main
    PUBLIC
        cpp-prover
)
