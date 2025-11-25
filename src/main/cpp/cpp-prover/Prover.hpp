#pragma once

#include "Assert.hpp"

#include <print>
#include <vector>

#include "TestInterface.hpp"
#include "TestRegistry.hpp"

#include "Ansi.hpp"

namespace prover
{
    struct Prover
    {
        static int test()
        {
            int failures = 0;
            for (const auto* test : TestRegistry::instance().all())
            {
                // TODO: capture results of tests here, use exceptions like junit? // do better
                try
                {
                    std::println(
                        "\n=====\n\nExecuting test: {}\nTest Source Location: {}:{}:{}\n",
                        ansi::Style(ansi::bold, ansi::Color(ansi::bright_white, test->name)),
                        test->source_location.file_name(),
                        test->source_location.line(),
                        test->source_location.column()
                    );
                    test->test();


                    std::println(
                    "Result: {}",
                     ansi::Style(ansi::bold, ansi::Color(ansi::green, "Passed")), test->name);
                }
                catch (const AssertionFailedException& exception)
                {
                    failures++;
                    std::println(
                        "Result: {}\nAssertion Source Location: {}:{}:{}\nError Message: {}\n",
                        ansi::Style(ansi::bold, ansi::Color(ansi::red, "Failed")),
                        exception.source_location().file_name(),
                        exception.source_location().line(),
                        exception.source_location().column(),
                        exception.what()
                    );
                }
                catch (const std::exception exception)
                {
                    // TODO : fail harder?
                    failures++;
                    std::println("\n---\n\nTest Failed: {}\nError Message: {}\n", test->name, exception.what());
                }
            }

            // TODO: do better, return a report or something.
            return failures;
        }
    };
}
