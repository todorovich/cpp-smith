#pragma once

#include "TestInterface.hpp"
#include "TestRegistry.hpp"
#include "Assert.hpp"
#include "TestResult.hpp"
#include "log/Logger.hpp"

#include <functional>
#include <regex>
#include <tuple>
#include <concepts>
#include <type_traits>

namespace test
{
    template <typename ReturnType, typename... Args>
    class Test final : public TestInterface
    {
        std::function<ReturnType(Args...)> _test_function;
        std::vector<std::tuple<Args...>> _arguments;
        std::source_location _source_location;
        std::string _output;

        static logging::Logger _getOrDefaultLogger(
            logging::Logger&& logger, const std::string_view name, std::string& output
            )
        {
            if (logger.getScope() != "")
            {
                return std::move(logger);
            }
            else
            {
                return logging::Logger{
                    std::string{name},
                    std::make_unique<logging::StringSink>(std::make_unique<logging::MinimalFormatter>(), output),
                    std::make_unique<logging::ConsoleSink>(std::make_unique<logging::MinimalFormatter>())
                };
            }

        }

        template <typename F>
            requires (std::invocable<F&> && std::same_as<void, std::invoke_result_t<F&>>)
        TestResult _test(F&& testFunction)
        {
            try
            {
                logger.print(
                    "\n=====\n\nTest Name: {}\nTest Source Location: {}:{}:{}\n",
                    ansi::Style(ansi::bold, ansi::Color(ansi::bright_white, name)),
                    source_location.file_name(),
                    source_location.line(),
                    source_location.column()
                );

                // Call the provided test function (must be callable as void())
                std::forward<F>(testFunction)();

                logger.print(
                    "Result: {}\n",
                    ansi::Style(ansi::bold, ansi::Color(ansi::green, "Passed")),
                    name
                );

                return TestResult(name, std::string{output()}, TestStatus::Passed);
            }
            catch (const faults::AssertionFailed& exception)
            {
                logger.print(
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
                logger.print(
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
                logger.print(
                    "Result: {}\n\n    An unknown type was thrown!\n",
                    ansi::Style(ansi::bold,
                        ansi::Background(ansi::bg_bright_red,
                            ansi::Color(ansi::black, "Test Failed")
                        )
                    )
                );
            }

            return TestResult(name, std::string{output()}, TestStatus::Failed);
        }

    public:
        Test(
            const std::string_view& name,
            std::function<ReturnType(Args...)> test_function,
            std::vector<std::tuple<Args...>> _args = {},
            logging::Logger logger = {},
            const std::source_location source_location = std::source_location::current()
        )
            : TestInterface(name, source_location, _getOrDefaultLogger(std::move(logger), name, _output))
            , _test_function(std::move(test_function))
            , _arguments(std::move(_args))
        {
            TestRegistry::instance().add(this);
        }

        std::pair<int, std::vector<TestResult>> test() noexcept override
        {
            if constexpr (sizeof...(Args) == 0)
            {
                TestResult test_result = _test([this] { _test_function(); });

                return {
                    test_result.status == TestStatus::Failed,
                    { std::move(test_result) }
                };
            }
            else
            {
                int failures = 0;
                std::vector<TestResult> results;

                for (auto& arg : _arguments)
                {
                    auto test_result = _test([this, &arg]{ std::apply(_test_function, arg); });

                    failures += test_result.status == TestStatus::Failed;
                    results.push_back(std::move(test_result));
                }

                return {failures, results};
            }
        }

        std::string_view output() const override
        {
            return _output;
        }
    };
}