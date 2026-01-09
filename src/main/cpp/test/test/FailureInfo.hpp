#pragma once

#include <format>
#include <source_location>
#include <stacktrace>

#include "Ansi.hpp"
#include "FailureKind.hpp"
#include "FormatHelper.hpp"

namespace test
{
	struct FailureInfo
	{
		FailureKind kind;
		std::string what;
		std::string message;
		std::stacktrace stacktrace;
		std::optional<std::source_location> location;
	};
}


template <>
struct std::formatter<test::FailureInfo>
{
    int indent = 4;
    bool use_ansi = false; // enabled only with ':a'

    constexpr auto parse(const std::format_parse_context& ctx)
    {
        auto it = ctx.begin();
        const auto end = ctx.end();

        // Accept a small "mini-language" in any order:
        //   a  -> enable ANSI
        //   iN -> indent subsequent lines by N spaces
        while (it != end && *it != '}')
        {
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
                if (v > 0) indent = v;
                continue;
            }

            throw std::format_error("invalid FailureInfo format (expected 'a' and/or 'iN')");
        }

        return it;
    }

    auto format(const test::FailureInfo& info, std::format_context& ctx) const
    {
        const std::string pad(static_cast<size_t>(indent), ' ');

        const std::string what = use_ansi ? info.what : ansi::strip_ansi(info.what);
        const std::string message = use_ansi ? info.message : ansi::strip_ansi(info.message);

        auto out = std::format_to(ctx.out(), "FailureInfo:\n{}kind: {}\n{}what: {}", pad, info.kind, pad, what);

        if (!message.empty())
        {
            const auto indented = test::FormatHelper::indent_multiline(message, pad);
            out = std::format_to(out, "\n{}message:\n{}{}", pad, pad, indented);
        }

        if (!info.stacktrace.empty())
        {
            out = std::format_to(out, "\n{}stacktrace:\n{}{}", pad, pad, info.stacktrace);
        }

        if (info.location.has_value())
        {
            out = std::format_to(
                out,
                "\n{}location: {}:{}:{}",
                pad,
                info.location->file_name(),
                info.location->line(),
                info.location->column()
            );
        }

        return out;
    }
};