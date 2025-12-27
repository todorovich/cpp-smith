#include <print>

#include "cpp-prover/Test.hpp"

#include "cpp-smith/compiler-probe/GccProbe.hpp"

namespace test
{
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        inline const static prover::Test<void> test {
        "GccProbe returns system includes",
            [] {

                const cpp_smith::GccProbe probe;
                const auto includes = probe.getSystemIncludes();

                prover::Assert::isFalse(includes.empty());

                for (const auto& path : includes) {
                    std::println("GCC include: {}", path.string());
                }
            }
        };
    };
}
