#include "Tester.hpp"

#include <vector>
#include <regex>


#include "TestInterface.hpp"
#include "TestRegistry.hpp"
#include "TestResult.hpp"
#include "algorithm/DependencyGraph.hpp"
#include "algorithm/TopologicalSort.hpp"

namespace test
{
    std::pair<int, std::vector<TestResult>> Tester::test()
    {
        int failures = 0;
        std::vector<TestResult> results;

        auto all_tests = TestRegistry::instance().all();
        std::vector<TestInterface*> tests_vec(all_tests.begin(), all_tests.end());

        cpp_smith::algorithm::DependencyGraph<TestInterface, std::string> graph(
            std::span<TestInterface*>(tests_vec),
            [](const TestInterface * t) { return t->name; },
            [](const TestInterface* t) { return t->dependencies(); }
        );

        const cpp_smith::algorithm::KahnsTopologicalSorter sorter(graph);

        for(const auto sorted = sorter.sorted(); auto* test : sorted)
        {
            log.print("\nExecuting Test: {}\n", test->name);

            auto [testFailures, testResults] = test->test();

            log.print("\nFinished Executing Test: {}\n", test->name);

            for (const auto& testResult : testResults)
            {
                log.print("\n{:a}\n", testResult);
            }

            failures += testFailures;

            results.insert(results.end(), testResults.begin(), testResults.end());
        }

        return {failures,  results};
    }
}
