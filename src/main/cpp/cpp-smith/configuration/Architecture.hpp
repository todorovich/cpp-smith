#pragma once

#include <format>

namespace cpp_smith
{
    enum class Architecture { X86, X64,  ARM_64};
}

template <> struct std::formatter<cpp_smith::Architecture> : formatter<string_view>
{
    auto format(const cpp_smith::Architecture value, format_context& ctx) const
    {
        string_view name;
        switch (value)
        {
            using enum cpp_smith::Architecture;
            case    X86:    name = "x86";       break;
            case    X64:    name = "x64";       break;
            case    ARM_64: name = "arm64";     break;
            default:        name = "unknown";
        }

        return formatter<string_view>::format(name, ctx);
    }
};
