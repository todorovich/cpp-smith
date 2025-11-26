#include "cpp-prover/Diff.hpp"
#include "cpp-prover/Test.hpp"

#include <string>
#include <regex>
#include <print>

namespace prover
{
    static void runAssertionTest(
        const std::function<void(const std::string&)>& assert,
        const std::function<void(const std::string&)>& assertFail,
        const std::string& expectedWhat,
        const std::string& function_call,
        const std::string& fail_function_call
    )
    {
        const std::string message = "custom message";

        try
        {
            assert(message);
        }
        catch (const std::exception& exception)
        {
            throw AssertionFailedException(
                std::format("{} threw {}", function_call, exception.what())
            );
        }

        try
        {
            assertFail(message);
        }
        catch (const AssertionFailedException& actual)
        {
            if (std::string{actual.what()} == expectedWhat)
            {
                std::string formattedWhat = actual.what();
                formattedWhat = std::regex_replace(formattedWhat, std::regex("\n"), "\n    ");
                std::println("Example Failure Output:\n\n    {}", formattedWhat);
                return;
            }

            throw AssertionFailedException(
                std::format("{} threw the wrong message\n\n{}",
                    function_call,
                    Diff(expectedWhat, actual.what()))
            );
        }
        catch (const std::exception& exception)
        {
            throw AssertionFailedException(
                std::format(
                    "{} threw {} instead of prover::AssertionFailedException",
                    fail_function_call,
                    exception.what()
                )
            );
        }

        throw AssertionFailedException(
           std::format("{} did not throw prover::AssertionFailedException", fail_function_call)
        );
    }
    
    static Test<void> areEqual(
        "Assert::areEqual",
        []()->void {
            const std::string expectedWhat =
                "Assert::areEqual Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:84:64\n"
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
    );

    static Test<void> areNotEqual(
        "Assert::areNotEqual",
        []()->void {
            const std::string expectedWhat =
                "Assert::areNotEqual Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:107:67\n"
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
    );

    static Test<void> areSame(
        "Assert::areSame",
        []()->void {
            const auto object_1 = std::make_unique<int>(47);
            const auto object_2 = object_1.get();
            const auto object_3 = object_1.get();

            const std::string expectedWhat =std::format(
                "Assert::areSame Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:141:36\n"
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
                [&](const std::string& message) {
                    Assert::areSame(*object_2,  *object_3, message);
                },
                [&](const std::string& message) {
                    Assert::areSame(object_2, object_3, message);
                },
                expectedWhat,
                "Assert::areSame(*object_2,  *object_3, message)",
                "Assert::areSame(object_2, object_3, message)"
            );
        }
    );

    static Test<void> areNotSame(
        "Assert::areNotSame",
        []()->void {
            const auto object_1 = std::make_unique<int>(47);
            const auto object_2 = object_1.get();
            const auto object_3 = object_1.get();

            const std::string expectedWhat =std::format(
                "Assert::areNotSame Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:170:39\n"
                "\n"
                "Provided objects share the same memory address\n"
                "Memory Address: {}\n",
                static_cast<const void*>(std::addressof(*object_2))
            );
            runAssertionTest(
                [&](const std::string& message) {
                    Assert::areNotSame(object_2, object_3, message);
                },
                [&](const std::string& message) {
                    Assert::areNotSame(*object_2,  *object_3, message);
                },
                expectedWhat,
                "Assert::areNotSame(object_2, object_3, message)",
                "Assert::areNotSame(*object_2,  *object_3, message)"
            );
        }
    );

    static Test<void> isTrue(
        "Assert::isTrue",
        []()->void {
            const std::string expectedWhat ="Assert::isTrue Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:198:35\n"
                "\n"
                "Provided expression evaluated to false\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-true\n"
                "+false\n";

            runAssertionTest(
                [&](const std::string& message) {
                    Assert::isTrue(true, message);
                },
                [&](const std::string& message) {
                    Assert::isTrue(false, message);
                },
                expectedWhat,
                "Assert::isTrue(true, message)",
                "Assert::isTrue(false, message)"
            );
        }
    );

    static Test<void> isFalse(
        "Assert::isFalse",
        []()->void {
            const std::string expectedWhat ="Assert::isFalse Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:226:36\n"
                "\n"
                "Provided expression evaluated to true\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-false\n"
                "+true\n";

            runAssertionTest(
                [&](const std::string& message) {
                    Assert::isFalse(false, message);
                },
                [&](const std::string& message) {
                    Assert::isFalse(true, message);
                },
                expectedWhat,
                "Assert::isFalse(false, message)",
                "Assert::isFalse(true, message)"
            );
        }
    );

    static Test<void> isNullptr(
        "Assert::isNullptr",
        []()->void {

            const auto pointer = std::make_unique<int>(42);

            auto pointer1 = pointer.get();

            const std::string expectedWhat = std::format(
                "Assert::isNullptr Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:262:38\n"
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
                [&](const std::string& message) {
                    Assert::isNullptr(nullptr, message);
                },
                [&](const std::string& message) {
                    Assert::isNullptr(pointer1, message);
                },
                expectedWhat,
                "Assert::isNullptr(nullptr, message)",
                "Assert::isNullptr(pointer1, message)"
            );
        }
    );

    static Test<void> isNotNullptr(
        "Assert::isNotNullptr",
        []()->void {

            const auto pointer = std::make_unique<int>(42);
            const auto pointer1 = pointer.get();

            const std::string expectedWhat =
                "Assert::isNotNullptr Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:295:41\n"
                "\n"
                "Provided pointer was nullptr\n"
                "\n"
                "--- expected\n"
                "+++ actual\n"
                "@@\n"
                "-!0x0\n"
                "+0x0\n";

            runAssertionTest(
                [&](const std::string& message) {
                    Assert::isNotNullptr(pointer1, message);
                },
                [&](const std::string& message) {
                    Assert::isNotNullptr(nullptr, message);
                },
                expectedWhat,
                "Assert::isNotNullptr(pointer1, message)",
                "Assert::isNotNullptr(nullptr, message)"
            );
        }
    );

    static Test<void> throwsException(
        "Assert::throwsException",
        []()->void {
            const std::string expectedWhat =
                "Assert::throwsException Failed: custom message\n"
                "Assertion Source Location: /home/micho/source/cpp-smith/src/test/cpp/prover/test_assert.cpp:321:63\n"
                "\n"
                "Assert::throws function did not throw\n";

            auto throwingLambda = []() { throw std::runtime_error("Test exception"); };
            auto nonThrowingLambda = []() { return; };

            runAssertionTest(
               [&](const std::string& message) {
                   Assert::throwsException<std::runtime_error>(throwingLambda, message);
               },
               [&](const std::string& message) {
                   Assert::throwsException<std::runtime_error>(nonThrowingLambda, message);
               },
               expectedWhat,
               "Assert::throwsException<std::exception>(throwingLambda, message)",
               "Assert::throwsException<std::exception>(nonThrowingLambda, message)"
           );
        }
    );
}
