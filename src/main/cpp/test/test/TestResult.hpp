#pragma once

#include <chrono>
#include <format>
#include <source_location>
#include <stacktrace>
#include <utility>

#include "Ansi.hpp"
#include "FailureKind.hpp"
#include "FailureInfo.hpp"
#include "FormatHelper.hpp"
#include "TestStatus.hpp"

namespace test
{
    struct TestResult
    {
        std::string name;
        std::string output;
        std::string terminal_output;
        TestStatus status;
        std::chrono::nanoseconds duration;
        std::source_location location;
        std::optional<FailureInfo> failure_info;

        TestResult() = delete;
        TestResult(TestResult&&) = default;
        TestResult(const TestResult&) = default;
        TestResult& operator=(TestResult&&) = default;
        TestResult& operator=(const TestResult&) = default;

        TestResult(
            std::string name,
            std::string terminalOutput,
            const TestStatus status,
            const std::chrono::nanoseconds duration,
            std::optional<FailureInfo> failureInfo = {}
        )
            : name(std::move(name))
            , output(ansi::strip_ansi(terminalOutput))
            , terminal_output(std::move(terminalOutput))
            , status(status)
            , duration(duration)
            , failure_info(failureInfo)
        {}

        bool operator==(TestResult const& other) const = default;
    };
}

template<>
struct std::hash<test::TestResult>
{
    size_t operator()(test::TestResult const& t) const noexcept
    {
        const size_t h1 = std::hash<std::string>{}(t.name);
        const size_t h2 = std::hash<std::string>{}(t.output);
        const size_t h3 = std::hash<std::underlying_type_t<test::TestStatus>>{}(std::to_underlying(t.status));
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

template <>
struct std::formatter<test::TestResult>
{
    bool use_ansi = false; // enabled only with ':a'
    int failure_indent = 4;

    constexpr auto parse(std::format_parse_context const& ctx)
    {
        auto it = ctx.begin();
        const auto end = ctx.end();

        while (it != end && *it != '}')
        {
            use_ansi = false;

            if (*it == 'a')
            {
                use_ansi = true;
                ++it;
                continue;
            }
            if (*it == 'i')
            {
                ++it;
                int v = 0;
                while (it != end && *it >= '0' && *it <= '9')
                {
                    v = v * 10 + (*it - '0');
                    ++it;
                }
                if (v > 0) failure_indent = v;
                continue;
            }

            throw std::format_error("invalid TestResult format (expected 'a' and/or 'iN')");
        }

        return it;
    }

    static constexpr std::string colorStatus(const test::TestStatus status)
    {
        switch (status)
        {
            using enum test::TestStatus;
            case Skipped:
                return ansi::Background(
                ansi::bg_yellow,
                ansi::Color(ansi::black, "Skipped")
                );
            case Passed: return ansi::Color(ansi::green, "Passed");
            case Failed: return ansi::Color(ansi::red, "Failed");
            default: return ansi::Background(
                ansi::bg_red,
                ansi::Color(ansi::black, "unknown")
            );
        }
    }

    auto format(const test::TestResult& result, std::format_context& ctx) const
    {
        auto out = ctx.out();

        if (use_ansi)
        {
            out = std::format_to(
               out,
               "{}\n"
               "  {} {}\n"
               "  {} {}\n"
               "  {} {}\n",
               ansi::Style(ansi::bold, "Test Result:"),
               ansi::Style(ansi::bold, "name:"), result.name,
               ansi::Style(ansi::bold, "status:"), colorStatus(result.status),
               ansi::Style(ansi::bold, "duration:"), test::FormatHelper::formatDuration(result.duration)
           );
        }
        else
        {
            out = std::format_to(
               out,
               "Test Result:\n"
               "  name: {}\n"
               "  status: {}\n"
               "  duration: {} ns",
               result.name,
               result.status,
               result.duration.count()
           );

            if (const auto chosen_output = std::string_view(result.output); !chosen_output.empty())
            {
                out = std::format_to(
                    out,
                    "\n  output:\n    {}",
                    test::FormatHelper::indent_multiline(chosen_output, "    ")
                );
            }

            if (result.failure_info.has_value())
            {
                // Build "{:aiN}" or "{:iN}" at runtime; custom spec can't be "{:i{}}".
                std::string spec;
                spec.reserve(16);
                spec += "{:";
                if (use_ansi) spec += 'a';
                spec += 'i';
                spec += std::to_string(failure_indent);
                spec += '}';

                const std::string formatted_failure =
                    std::vformat(spec, std::make_format_args(*result.failure_info));

                out = std::format_to(out, "\n  failure:\n    {}", formatted_failure);
            }
        }

        return out;
    }
};
