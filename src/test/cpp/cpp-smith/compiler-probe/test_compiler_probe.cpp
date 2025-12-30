#include "test/Test.hpp"

#include "compiler-probe/GccProbe.hpp"

namespace test
{
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        inline static logging::Logger logger = logging::Logger::defaultLogger("test::Tests");

        inline const static test::Test<void> test {
        "GccProbe returns system includes",
            [] {

                const GccProbe probe;
                const auto includes = probe.getSystemIncludes();

                Assert::isFalse(includes.empty());

                for (const auto& path : includes) {
                    logger.print("GCC include: {}", path.string());
                }
            }
        };
    };
}
