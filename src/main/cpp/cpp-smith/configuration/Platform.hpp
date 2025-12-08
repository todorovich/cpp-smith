#pragma once

#include <format>

namespace cpp_smith
{
    enum class Platform { LINUX, WINDOWS, MAC_OS };
}

template <> struct std::formatter<cpp_smith::Platform> : formatter<string_view>
{
    auto format(const cpp_smith::Platform value, format_context& ctx) const
    {
        string_view name;
        switch (value)
        {
            using enum cpp_smith::Platform;
            case    LINUX:      name = "Linux";     break;
            case    WINDOWS:    name = "Windows";   break;
            case    MAC_OS:     name = "Mac OS";    break;
            default:            name = "unknown";
        }

        return formatter<string_view>::format(name, ctx);
    }
};

