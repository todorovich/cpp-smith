#include <string>
#include <regex>
#include <print>
#include <concepts>
#include <type_traits>

#include "../../../main/cpp/faults/faults/faults.hpp"

#include "../../../main/cpp/test/test/Diff.hpp"
#include "test/Test.hpp"

using namespace test;

namespace assert_tests
{
    template <typename F>
    concept AssertCallable = std::invocable<F, const std::string&>
        && std::same_as<void, std::invoke_result_t<F, const std::string&>>;

    struct Tests
    {
        Tests() = delete;

        inline static logging::Logger logger = logging::Logger::defaultLogger("test::Tests");

        template <AssertCallable AssertFn, AssertCallable AssertFailFn>
        static void runAssertionTest(
            AssertFn&& assert,
            AssertFailFn&& assertFail,
            const std::string& expectedWhat,
            const std::string& function_call,
            const std::string& fail_function_call
        )
        {
            static_assert(AssertCallable<AssertFn>,
                "runAssertionTest: first parameter must be callable with (const std::string&) and return void");
            static_assert(AssertCallable<AssertFailFn>,
                "runAssertionTest: second parameter must be callable with (const std::string&) and return void");
            const std::string message = "custom message";

            try
            {
                assert(message);
            }
            catch (const std::exception& exception)
            {
                throw faults::violated::Assertion(
                    std::format("{} threw {}", function_call, exception.what())
                );
            }

            try
            {
                assertFail(message);
            }
            catch (const faults::violated::Assertion& actual)
            {
                if (std::string{actual.message} == expectedWhat)
                {
                    std::string formattedWhat = actual.message;
                    formattedWhat = std::regex_replace(formattedWhat, std::regex("\n"), "\n    ");
                    logger.print("Example Failure Message:\n\n    {}", formattedWhat);
                    return;
                }

                throw faults::violated::Assertion(
                    std::format("{} threw the wrong message\n\n{}",
                        function_call,
                        Diff(expectedWhat, actual.message))
                );
            }
            catch (const std::exception& exception)
            {
                throw faults::violated::Assertion(
                    std::format(
                        "{} threw {} instead of prover::AssertionFailedException",
                        fail_function_call,
                        exception.what()
                    )
                );
            }

            throw faults::violated::Assertion(
               std::format("{} did not throw prover::AssertionFailedException", fail_function_call)
            );
        }

        static void testAreEqual()
        {
            const std::string expectedWhat =
                "Assert::areEqual Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:103:64\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-47\n"
                "+42\n";


            runAssertionTest(
                [](const std::string& message){Assert::areEqual(42, 42, message);},
                [](const std::string& message){Assert::areEqual(47, 42, message);},
                expectedWhat,
                "Assert::areEqual(42, 42, message)",
                "Assert::areEqual(47, 42, message)"
            );
        }

        inline const static Test<void> areEqual {"Assert::areEqual", testAreEqual };

        static void testAreNotEqual()
        {
            const std::string expectedWhat =
                "Assert::areNotEqual Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:126:67\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-47\n"
                "+47\n";

            runAssertionTest(
                [](const std::string& message){Assert::areNotEqual(47, 42, message);},
                [](const std::string& message){Assert::areNotEqual(47, 47, message);},
                expectedWhat,
                "Assert::areNotEqual(47, 42, message)",
                "Assert::areNotEqual(47, 47, message)"
            );
        }

        inline const static Test<void> areNotEqual {"Assert::areNotEqual", testAreNotEqual };

        static void testAreSame()
        {
            const auto object_1 = std::make_unique<int>(47);
            const auto object_2 = object_1.get();
            const auto object_3 = object_1.get();

            const std::string expectedWhat =std::format(
                "Assert::areSame Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:160:36\n"
                "\n"
                "Provided objects do not share the same memory address\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-{}\n"
                "+{}\n",
                static_cast<const void*>(std::addressof(object_2)),
                static_cast<const void*>(std::addressof(object_3))
            );
            runAssertionTest(
                [&object_2, &object_3](const std::string& message) {
                    Assert::areSame(*object_2,  *object_3, message);
                },
                [&object_2, &object_3](const std::string& message) {
                    Assert::areSame(object_2, object_3, message);
                },
                expectedWhat,
                "Assert::areSame(*object_2,  *object_3, message)",
                "Assert::areSame(object_2, object_3, message)"
            );
        }

        inline const static Test<void> areSame {"Assert::areSame", testAreSame };

        static void testAreNotSame()
        {
            const auto object_1 = std::make_unique<int>(47);
            const auto object_2 = object_1.get();
            const auto object_3 = object_1.get();

            const std::string expectedWhat =std::format(
                "Assert::areNotSame Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:189:39\n"
                "\n"
                "Provided objects share the same memory address\n"
                "Memory Address: {}\n",
                static_cast<const void*>(std::to_address(object_2))
            );
            runAssertionTest(
                [&object_2, &object_3](const std::string& message) {
                    Assert::areNotSame(object_2, object_3, message);
                },
                [&object_2](const std::string& message) {
                    Assert::areNotSame(*object_2,  *object_2, message);
                },
                expectedWhat,
                "Assert::areNotSame(object_2, object_3, message)",
                "Assert::areNotSame(*object_2,  *object_3, message)"
            );
        }

        inline const static Test<void> areNotSame { "Assert::areNotSame", testAreNotSame };

        static void testIsTrue()
        {
            const std::string expectedWhat ="Assert::isTrue Failed: custom message\n"
                    "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:217:35\n"
                    "\n"
                    "Provided expression evaluated to false\n"
                    "\n"
                    "--- expected\n"
                    "+++ actual\n"
                    "@@\n"
                    "-true\n"
                    "+false\n";

            runAssertionTest(
                [](const std::string& message) {
                    Assert::isTrue(true, message);
                },
                [](const std::string& message) {
                    Assert::isTrue(false, message);
                },
                expectedWhat,
                "Assert::isTrue(true, message)",
                "Assert::isTrue(false, message)"
            );
        }

        inline const static Test<void> isTrue {"Assert::isTrue",testIsTrue };

        static void testIsFalse()
        {
            const std::string expectedWhat ="Assert::isFalse Failed: custom message\n"
                    "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:245:36\n"
                    "\n"
                    "Provided expression evaluated to true\n"
                    "\n"
                    "--- expected\n"
                    "+++ actual\n"
                    "@@\n"
                    "-false\n"
                    "+true\n";

            runAssertionTest(
                [](const std::string& message) {
                    Assert::isFalse(false, message);
                },
                [](const std::string& message) {
                    Assert::isFalse(true, message);
                },
                expectedWhat,
                "Assert::isFalse(false, message)",
                "Assert::isFalse(true, message)"
            );
        }

        inline const static Test<void> isFalse { "Assert::isFalse", testIsFalse };

        static void testIsNullptr()
        {
            const auto pointer = std::make_unique<int>(42);

            const auto pointer1 = pointer.get();

            const std::string expectedWhat = std::format(
                "Assert::isNullptr Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:280:38\n"
                "\n"
                "Provided pointer was not nullptr\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-0x0\n"
                "+{}\n",
                static_cast<void*>(pointer1)
            );

            runAssertionTest(
                [](const std::string& message) {
                    Assert::isNullptr(nullptr, message);
                },
                [&pointer1](const std::string& message) {
                    Assert::isNullptr(pointer1, message);
                },
                expectedWhat,
                "Assert::isNullptr(nullptr, message)",
                "Assert::isNullptr(pointer1, message)"
            );
        }

        inline const static Test<void> isNullptr {"Assert::isNullptr", testIsNullptr };

        static void testIsNotNullptr()
        {
            const auto pointer = std::make_unique<int>(42);
            const auto pointer1 = pointer.get();

            const std::string expectedWhat =
                "Assert::isNotNullptr Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:312:41\n"
                "\n"
                "Provided pointer was nullptr\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-!0x0\n"
                "+0x0\n";

            runAssertionTest(
                [&pointer1](const std::string& message) {
                    Assert::isNotNullptr(pointer1, message);
                },
                [](const std::string& message) {
                    Assert::isNotNullptr(nullptr, message);
                },
                expectedWhat,
                "Assert::isNotNullptr(pointer1, message)",
                "Assert::isNotNullptr(nullptr, message)"
            );
        }

        inline const static Test<void> isNotNullptr { "Assert::isNotNullptr", testIsNotNullptr };

        static void testThrowsException()
        {
            const std::string expectedWhat =
                "Assert::throwsException Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:338:70\n"
                "\n"
                "Assert::throws function did not throw\n";

            runAssertionTest(
               [](const std::string& message) {
                   Assert::throwsException<faults::invalid::Argument>(
                       [] { throw faults::invalid::Argument("Test exception"); },
                       message
                    );
               },
               [](const std::string& message) {
                   Assert::throwsException<faults::invalid::Argument>(
                       [] { logger.print("don't throw"); },
                       message
                    );
               },
               expectedWhat,
               "Assert::throwsException<exceptions::InvalidInput>(throwingLambda, message)",
               "Assert::throwsException<exceptions::InvalidInput>(nonThrowingLambda, message)"
           );
        }

        inline const static Test<void> throwsException { "Assert::throwsException", testThrowsException };
    };
}
