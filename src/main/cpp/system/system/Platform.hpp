#pragma once

// Wrap platform detection macros in constexpr variables.

namespace Platform {

#if defined(_WIN32)
    static constexpr bool is_windows = true;
#else
    static constexpr bool is_windows = false;
#endif

#if defined(__linux__)
    static constexpr bool is_linux = true;
#else
    static constexpr bool is_linux = false;
#endif

#if defined(__APPLE__)
    static constexpr bool is_macos = true;
#else
    static constexpr bool is_macos = false;
#endif

}
