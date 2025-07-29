#include "cpp-smith/compiler-probe/CompilerProbe.hpp"
#include <catch2/catch_test_macros.hpp>
#include <print>

#if defined(_WIN32)
TEST_CASE("MsvcProbe returns system includes", "[msvcprobe]") {
    MsvcProbe probe;
    auto includes = probe.getSystemIncludes();
    REQUIRE_FALSE(includes.empty());
    for (const auto& path : includes) {
        std::println("MSVC include: {}", path.string());
    }
}
#else
TEST_CASE("GccProbe returns system includes", "[gccprobe]") {
    GccProbe probe;
    auto includes = probe.getSystemIncludes();
    REQUIRE_FALSE(includes.empty());
    for (const auto& path : includes) {
        std::println("GCC include: {}", path.string());
    }
}

TEST_CASE("ClangProbe returns system includes", "[clangprobe]") {
    ClangProbe probe;
    auto includes = probe.getSystemIncludes();
    REQUIRE_FALSE(includes.empty());
    for (const auto& path : includes) {
        std::println("Clang include: {}", path.string());
    }
}
#endif
