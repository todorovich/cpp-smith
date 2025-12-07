#include "cpp-smith/compiler-probe/GccProbe.hpp"

#include "cpp-prover/Test.hpp"

#include <print>

[[maybe_unused]] const static prover::Test<void> test(
    "GccProbe returns system includes",
    [] {

        const cpp_smith::GccProbe probe;
        const auto includes = probe.getSystemIncludes();

        prover::Assert::isFalse(includes.empty());

        for (const auto& path : includes) {
            std::println("GCC include: {}", path.string());
        }
    }
);
