add_library(cpp-prover STATIC)

target_include_directories(cpp-prover PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(cpp-prover PRIVATE -fno-modules-ts)

target_sources(cpp-prover
    PRIVATE
        Prover.cpp
    PUBLIC
        Prover.hpp
        prover_main.hpp
        Test.hpp
        TestInterface.hpp
        TestRegistry.hpp
)