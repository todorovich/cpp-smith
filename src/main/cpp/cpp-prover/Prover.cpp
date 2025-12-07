#include "Prover.hpp"

#include <vector>
#include <regex>

#include "Assert.hpp"
#include "TestInterface.hpp"
#include "TestRegistry.hpp"
#include "TestResult.hpp"

#include "Ansi.hpp"



namespace prover
{
    std::pair<int, std::vector<TestResult>> Prover::test()
    {
        int failures = 0;
        std::vector<TestResult> results;

        for (auto* test : TestRegistry::instance().all())
        {
            try
            {
                test->logger.print(
                    "\n=====\n\nTest Name: {}\nTest Source Location: {}:{}:{}\n",
                    ansi::Style(ansi::bold, ansi::Color(ansi::bright_white, test->name)),
                    test->source_location.file_name(),
                    test->source_location.line(),
                    test->source_location.column()
                );

                test->test();

                test->logger.print(
                    "Result: {}\n",
                    ansi::Style(ansi::bold, ansi::Color(ansi::green, "Passed")),
                    test->name
                );
            }
            catch (const exceptions::AssertionFailed& exception)
            {
                failures++;
                 test->logger.print(
                    "\nResult: {}\nAssertion Source Location: {}:{}:{}\nWhat: {}\nMessage:\n    {}\n\nStack Trace:\n{}\n",
                    ansi::Style(ansi::bold, ansi::Color(ansi::red, "Assertion Failed")),
                    exception.source_location.file_name(),
                    exception.source_location.line(),
                    exception.source_location.column(),
                    exception.what(),
                    std::regex_replace(exception.message, std::regex("\n"), "\n    "),
                    exception.stacktrace
                );
            }
            catch (const std::exception& exception) //NOSONAR
            {
                failures++;
                 test->logger.print(
                    "Result: {}\nstd::exception::what():\n    {}\n",
                    ansi::Style(ansi::bold,
                        ansi::Background(ansi::bg_black,
                            ansi::Color(ansi::bright_red, "Test Failed")
                        )
                    ),
                    std::regex_replace(exception.what(), std::regex("\n"), "\n    ")
                );
            }
            catch (...)
            {
                failures++;
                test->logger.print(
                    "Result: {}\n\n    An unknown type was thrown!\n",
                    ansi::Style(ansi::bold,
                        ansi::Background(ansi::bg_bright_red,
                            ansi::Color(ansi::black, "Test Failed")
                        )
                    )
                );
            }

            results.emplace_back(
                test->name,
                std::string{test->output()},
                failures > 0 ? TestStatus::Failed : TestStatus::Passed
            );
        }

        return {failures,  results};
    }
}
