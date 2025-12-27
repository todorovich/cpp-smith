#pragma once

#include <utility>

#include "Ansi.hpp"

namespace test
{
    enum class TestStatus { Skipped = -1, Passed = 0, Failed = 1 };

    struct TestResult
    {
        std::string name;
        std::string output;
        std::string terminal_output;
        TestStatus status;

        TestResult() = delete;
        TestResult(TestResult&&) = default;
        TestResult(const TestResult&) = default;
        TestResult& operator=(TestResult&&) = default;
        TestResult& operator=(const TestResult&) = default;

        TestResult(std::string name, std::string terminalOutput, const TestStatus status)
            : name(std::move(name))
            , output(ansi::strip_ansi(terminalOutput))
            , terminal_output(std::move(terminalOutput))
            , status(status)
        {}

        bool operator==(TestResult const& other) const = default;
    };
}

template<>
struct std::hash<test::TestResult> {
    size_t operator()(test::TestResult const& t) const noexcept {
        size_t h1 = std::hash<std::string>{}(t.name);
        size_t h2 = std::hash<std::string>{}(t.output);
        size_t h3 = std::hash<std::underlying_type_t<test::TestStatus>>{}(std::to_underlying(t.status));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
