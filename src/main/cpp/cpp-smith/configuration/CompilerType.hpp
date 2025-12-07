#pragma once

#include <format>

namespace cpp_smith
{
    // TODO: the compiler version should end up being used somewhere.
    enum class CompilerType { GCC, CLANG, MSVC };
}

template <> struct std::formatter<cpp_smith::CompilerType> : formatter<string_view>
{
    auto format(const cpp_smith::CompilerType value, format_context& ctx) const
    {
        using cpp_smith::CompilerType;
        string_view name = "unknown";

        switch (value)
        {
        case CompilerType::GCC:
            name = "GCC";
            break;

        case CompilerType::CLANG:
            name = "Clang";
            break;

        case CompilerType::MSVC:
            name = "MSVC";
            break;
        }

        return formatter<string_view>::format(name, ctx);
    }
};

