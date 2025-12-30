#include "Tester.hpp"

#include <vector>
#include <regex>

#include "Assert.hpp"
#include "TestInterface.hpp"
#include "TestRegistry.hpp"
#include "TestResult.hpp"

#include "Ansi.hpp"

namespace test
{
    std::pair<int, std::vector<TestResult>> Tester::test()
    {
        int failures = 0;
        std::vector<TestResult> results;

        for (auto* test : TestRegistry::instance().all())
        {
            auto [testFailures, testResults] = test->test();

            failures += testFailures;

            results.insert(results.end(), testResults.begin(), testResults.end());
        }

        return {failures,  results};
    }
}
