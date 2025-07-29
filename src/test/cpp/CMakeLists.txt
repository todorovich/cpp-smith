add_library(test_definitions INTERFACE
        ../data/no_includes.cpp)

target_compile_definitions(test_definitions INTERFACE CPP_SMITH_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\")
target_compile_definitions(test_definitions INTERFACE TEST_DATA_DIR=\"${CMAKE_SOURCE_DIR}/src/test/data\")

target_include_directories(test_definitions INTERFACE ${CMAKE_SOURCE_DIR}/src/main/cpp/)

add_subdirectory(cpp-smith)
