#include "cpp-smith/compiler-probe/GccProbe.hpp"

#include "cpp-prover/Test.hpp"

#include <print>

static prover::Test<void> test(
    "GccProbe returns system includes",
    []()->void {

        cpp_smith::GccProbe probe;
        auto includes = probe.getSystemIncludes();

        prover::Assert::isFalse(includes.empty());

        for (const auto& path : includes) {
            std::println("GCC include: {}", path.string());
        }
    }
);
