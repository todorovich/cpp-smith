#pragma once

#include "Ansi.hpp"

namespace prover
{
    enum class TestStatus { Skipped = -1, Passed = 0, Failed = 1 };

    struct TestResult
    {
        const std::string name;
        const std::string output;
        const std::string terminal_output;
        const TestStatus status;

        TestResult() = delete;
        TestResult(TestResult&&) = default;
        TestResult(const TestResult&) = default;
        TestResult& operator=(TestResult&&) = delete;
        TestResult& operator=(const TestResult&) = delete;

        TestResult(std::string name, std::string terminalOutput, const TestStatus status)
            : name(std::move(name))
            , output(ansi::strip_ansi(terminalOutput))
            , terminal_output(std::move(terminalOutput))
            , status(status)
        {}

        bool operator==(TestResult const& other) const {
            return name == other.name &&
                   output == other.output &&
                   status == other.status;
        }
    };
}

inline bool operator==(const prover::TestResult& left, const prover::TestResult& right)
{
    return left.name == right.name &&
           left.output == right.output &&
           left.status == right.status;
}

template<>
struct std::hash<prover::TestResult> {
    size_t operator()(prover::TestResult const& t) const noexcept {
        size_t h1 = std::hash<std::string>{}(t.name);
        size_t h2 = std::hash<std::string>{}(t.output);
        size_t h3 = std::hash<int>{}(static_cast<int>(t.status));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};
