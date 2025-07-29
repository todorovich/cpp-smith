cmake_minimum_required(VERSION 3.28)
project(cpp-smith)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.4 # or latest stable
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

add_subdirectory(src/main/cpp)
add_subdirectory(src/test/cpp)
