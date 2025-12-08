#pragma once

#include <string>
#include <format>
#include <utility>
#include <memory>
#include <exception>

#include "Diff.hpp"
#include "Exceptions.hpp"

template <typename T>
concept DerivedFromException = std::derived_from<T, std::exception>
                          && !std::same_as<T, std::exception>;

namespace prover
{
    template <typename T>
    concept Pointer = std::is_pointer_v<T> || std::is_null_pointer_v<T>;

    template <typename F>
    concept Function = requires(F f) {
        { f() };
    };
    

    class Assert
    {
        static std::string formatUserMessage(const std::string& message)
        {
            if (message.empty())
            {
                return "";
            }

            return std::format("\nMessage: {}", message);
        }

      public:
        Assert() = delete;

        template <typename ExpectedT, typename ActualT>
            requires std::equality_comparable_with<ExpectedT, ActualT>
        [[maybe_unused]] static const ActualT& areEqual(
            const ExpectedT& expected,
            const ActualT& actual,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (!(expected == actual))
            {
                fail(
                    std::format(
                        "Assert::areEqual Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff(std::format("{}",expected), std::format("{}",actual))
                    ),
                    source_location
                );
            }

            return actual;
        }

        template <typename ExpectedT, typename ActualT>
            requires std::equality_comparable_with<ExpectedT, ActualT>
        static void areNotEqual(
            const ExpectedT& first,
            const ActualT& second,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (first == second)
            {
                fail(
                    std::format(
                        "Assert::areNotEqual Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff(std::format("{}",first), std::format("{}",second))
                    ),
                    source_location
                );
            }
        }

        template <typename A, typename B>
        static void areSame(
            const A& firstValue,
            const B& secondValue,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            auto addressA = static_cast<const void*>(std::addressof(firstValue));
            auto addressB = static_cast<const void*>(std::addressof(secondValue));

            if (addressA != addressB)
            {
                fail(
                    std::format(
                        "Assert::areSame Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided objects do not share the same memory address\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff(
                            std::format("{}",addressA),
                            std::format("{}",addressB)
                        )
                    ),
                    source_location
                );
            }
        }

        template <typename A, typename B>
        static void areNotSame(
            const A& firstValue,
            const B& secondValue,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (std::addressof(firstValue) == std::addressof(secondValue))
            {
                fail(
                    std::format(
                        "Assert::areNotSame Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided objects share the same memory address\n"
                        "Memory Address: {}\n",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        static_cast<const void*>(std::addressof(firstValue))
                    ),
                    source_location
                );
            }
        }

        static void isFalse(
            const bool expression,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (expression)
            {
                fail(
                    std::format(
                        "Assert::isFalse Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided expression evaluated to true\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff("false", "true")
                    ),
                    source_location
               );
            }
        }

        static void isTrue(
            const bool expression,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (!expression)
            {
                fail(
                    std::format(
                        "Assert::isTrue Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided expression evaluated to false\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff("true", "false")
                    ),
                    source_location
                );
            }
        }

        static void isNullptr(
            Pointer auto pointer,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (pointer != nullptr)
            {
                fail(
                    std::format(
                        "Assert::isNullptr Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided pointer was not nullptr\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff(
                            std::format("{}", static_cast<const void*>(nullptr)),
                            std::format("{}", static_cast<const void*>(pointer))
                        )
                    ),
                    source_location
               );
            }
        }

        static void isNotNullptr(
            Pointer auto pointer,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            if (pointer == nullptr)
            {
                fail(
                    std::format(
                        "Assert::isNotNullptr Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "Provided pointer was nullptr\n"
                        "\n"
                        "{}",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        Diff(
                            std::format("!{}", static_cast<const void*>(nullptr)),
                            std::format("{}", static_cast<const void*>(pointer))
                        )
                    ),
                    source_location
               );
            }
        }

        template <DerivedFromException ExceptionT>
        static void throwsException(
            Function auto&& function,
            const std::string& message = {},
            const std::source_location& source_location = std::source_location::current()
        )
        {
            try
            {
                function();
                fail("Assert::throws function did not throw", source_location);
            }
            catch (const ExceptionT& ignored) // NOSONAR
            {
                /* this is the success case */
            }
            catch (const exceptions::CppSmithException& exception) {
                fail(
                    std::format(
                        "Assert::throwsException Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "{}\n",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        exception.message,
                        "",
                        ""
                    ),
                    source_location
                );
            }
            catch (const std::exception& exception) {
                fail(
                    std::format(
                        "Assert::throwsException Failed: {}\n"
                        "Assertion Source Location: {}:{}:{}\n"
                        "\n"
                        "What: {}\n",
                        message,
                        source_location.file_name(),
                        source_location.line(),
                        source_location.column(),
                        exception.what(),
                        "",
                        ""
                    ),
                    source_location
                );
            }
        }

        // Existing simple overload is fine to keep:
        [[noreturn]] static void fail(
            const std::string& message,
            const std::source_location& source_location = std::source_location::current(),
            const std::stacktrace& stacktrace = std::stacktrace::current()
        )
        {
            throw exceptions::AssertionFailed(message, source_location, stacktrace);
        }
    };
}