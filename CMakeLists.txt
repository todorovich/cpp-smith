cmake_minimum_required(VERSION 3.28)
project(cpp-smith)

set(CMAKE_CXX_STANDARD 26)

enable_testing()

add_subdirectory(src/main/cpp)
add_subdirectory(src/test/cpp)
