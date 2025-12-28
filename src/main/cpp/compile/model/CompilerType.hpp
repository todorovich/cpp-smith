#pragma once

#include <format>

namespace cpp_smith
{
    enum class CompilerType { GCC, CLANG, MSVC };
}

template <> struct std::formatter<cpp_smith::CompilerType> : formatter<string_view>
{
    auto format(const cpp_smith::CompilerType value, format_context& ctx) const
    {
        string_view name;
        switch (value)
        {
            using enum cpp_smith::CompilerType;
            case    GCC:    name = "GCC";       break;
            case    CLANG:  name = "Clang";     break;
            case    MSVC:   name = "MSVC";      break;
            default:        name = "unknown";
        }

        return formatter<string_view>::format(name, ctx);
    }
};

