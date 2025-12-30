 #pragma once

#include <format>

namespace test
{
    class Diff
    {
        static std::string prefix_lines(std::string_view text, const char prefix)
        {
            // count '\n'
            std::size_t new_line = 0;
            for (const char character : text) if (character == '\n') ++new_line;

            // reserve: original + (nl + 1) prefixes + newline at end
            std::string out;
            out.reserve(text.size() + (new_line + 1) * 2);

            out.push_back(prefix);

            std::size_t start = 0;
            while (true)
            {
                const std::size_t index = text.find('\n', start);
                if (index == std::string_view::npos)
                {
                    out.append(text.substr(start));
                    out.push_back('\n');
                    break;
                }

                out.append(text.substr(start, index - start + 1)); // include '\n'
                out.push_back(prefix);
                start = index + 1;
            }

            return out;
        }

        std::string _diff;

    public:
        Diff(const std::string& expected, const std::string& actual)
        {
            _diff = std::format(
                "--- expected\n+++ actual\n@@\n{}{}",
                prefix_lines(expected, '-'),
                prefix_lines(actual,  '+')
            );
        }

        explicit Diff(const std::string_view sv) : _diff(sv) {}

        explicit operator std::string() const { return _diff; }
        explicit operator std::string_view() const { return std::string_view{_diff}; }

        [[nodiscard]] const char* data() const noexcept { return _diff.data(); }
        [[nodiscard]] const char* c_str() const noexcept { return _diff.c_str(); }
        [[nodiscard]] std::size_t size() const noexcept { return _diff.size(); }
        [[nodiscard]] std::size_t length() const noexcept { return _diff.length(); }
    };
}

template<>
struct std::formatter<test::Diff>
    : std::formatter<std::string_view>
{
    auto format(const test::Diff& d,
                std::format_context& ctx) const
    {
        // cast to string_view → use std::formatter<string_view>
        return std::formatter<std::string_view>::format(
            static_cast<std::string_view>(d), ctx
        );
    }
};
