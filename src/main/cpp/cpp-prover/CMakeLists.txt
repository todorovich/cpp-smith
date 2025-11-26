add_library(cpp-prover STATIC)

target_include_directories(cpp-prover PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(cpp-prover
    PRIVATE
        Prover.cpp
    PUBLIC
        Prover.hpp
        Test.hpp
        TestInterface.hpp
        TestRegistry.hpp
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
