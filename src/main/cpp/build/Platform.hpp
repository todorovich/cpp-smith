#pragma once

// Wrap platform detection macros in constexpr variables.

namespace platform {

#if defined(_WIN32)
    inline constexpr bool is_windows = true;
#else
    inline constexpr bool is_windows = false;
#endif

#if defined(__linux__)
    inline constexpr bool is_linux = true;
#else
    inline constexpr bool is_linux = false;
#endif

#if defined(__APPLE__)
    inline constexpr bool is_macos = true;
#else
    inline constexpr bool is_macos = false;
#endif

} // namespace platform
