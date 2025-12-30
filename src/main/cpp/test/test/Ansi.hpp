#pragma once

#include <string>
#include <string_view>

namespace ansi
{
    inline constexpr std::string default_fg  = "\x{1b}[39m";
    inline constexpr std::string default_bg  = "\x{1b}[49m";
    inline constexpr std::string reset       = "\x{1b}[0m";

    inline constexpr std::string black       = "\x{1b}[30m";
    inline constexpr std::string red         = "\x{1b}[31m";
    inline constexpr std::string green       = "\x{1b}[32m";
    inline constexpr std::string yellow      = "\x{1b}[33m";
    inline constexpr std::string blue        = "\x{1b}[34m";
    inline constexpr std::string magenta     = "\x{1b}[35m";
    inline constexpr std::string cyan        = "\x{1b}[36m";
    inline constexpr std::string white       = "\x{1b}[37m";

    inline constexpr std::string bright_black   = "\x{1b}[90m";
    inline constexpr std::string bright_red     = "\x{1b}[91m";
    inline constexpr std::string bright_green   = "\x{1b}[92m";
    inline constexpr std::string bright_yellow  = "\x{1b}[93m";
    inline constexpr std::string bright_blue    = "\x{1b}[94m";
    inline constexpr std::string bright_magenta = "\x{1b}[95m";
    inline constexpr std::string bright_cyan    = "\x{1b}[96m";
    inline constexpr std::string bright_white   = "\x{1b}[97m";

    inline constexpr std::string bg_black       = "\x{1b}[40m";
    inline constexpr std::string bg_red         = "\x{1b}[41m";
    inline constexpr std::string bg_green       = "\x{1b}[42m";
    inline constexpr std::string bg_yellow      = "\x{1b}[43m";
    inline constexpr std::string bg_blue        = "\x{1b}[44m";
    inline constexpr std::string bg_magenta     = "\x{1b}[45m";
    inline constexpr std::string bg_cyan        = "\x{1b}[46m";
    inline constexpr std::string bg_white       = "\x{1b}[47m";

    inline constexpr std::string bg_bright_black   = "\x{1b}[100m";
    inline constexpr std::string bg_bright_red     = "\x{1b}[101m";
    inline constexpr std::string bg_bright_green   = "\x{1b}[102m";
    inline constexpr std::string bg_bright_yellow  = "\x{1b}[103m";
    inline constexpr std::string bg_bright_blue    = "\x{1b}[104m";
    inline constexpr std::string bg_bright_magenta = "\x{1b}[105m";
    inline constexpr std::string bg_bright_cyan    = "\x{1b}[106m";
    inline constexpr std::string bg_bright_white   = "\x{1b}[107m";

    inline constexpr std::string bold          = "\x{1b}[1m";
    inline constexpr std::string dim           = "\x{1b}[2m";
    inline constexpr std::string italic        = "\x{1b}[3m";
    inline constexpr std::string underline     = "\x{1b}[4m";
    inline constexpr std::string blink         = "\x{1b}[5m";
    inline constexpr std::string reverse       = "\x{1b}[7m";
    inline constexpr std::string hidden        = "\x{1b}[8m";
    inline constexpr std::string strikethrough = "\x{1b}[9m";

    inline constexpr std::string normal        = "\x{1b}[22m";
    inline constexpr std::string not_italic    = "\x{1b}[23m";
    inline constexpr std::string not_underline = "\x{1b}[24m";
    inline constexpr std::string not_blink     = "\x{1b}[25m";
    inline constexpr std::string not_reverse   = "\x{1b}[27m";
    inline constexpr std::string not_hidden    = "\x{1b}[28m";
    inline constexpr std::string not_strike    = "\x{1b}[29m";

    constexpr std::string_view StyleEnd(const std::string_view s) {
        if (s == bold)          return normal;
        if (s == dim)           return normal;
        if (s == italic)        return not_italic;
        if (s == underline)     return not_underline;
        if (s == blink)         return not_blink;
        if (s == reverse)       return not_reverse;
        if (s == hidden)        return not_hidden;
        if (s == strikethrough) return not_strike;
        return reset;
    }

    constexpr std::string build(const std::string_view pre, const std::string_view text, const std::string_view suf)
    {
        std::string out;
        out.reserve(pre.size() + text.size() + suf.size());
        out.append(pre);
        out.append(text);
        out.append(suf);
        return out;
    }

    constexpr std::string Color(const std::string_view code,const std::string_view text)
    {
        return build(code, text, default_fg);
    }

    constexpr std::string Background(const std::string_view code, const std::string_view text)
    {
        return build(code, text, default_bg);
    }

    constexpr std::string Style(const std::string_view attr, const std::string_view text)
    {
        return build(attr, text, StyleEnd(attr));
    }

    static constexpr bool is_escape_sequence(char c) {
        return c == '\x{1B}';
    }

    static constexpr bool is_control_sequence_terminator(char c) {
        return c >= '@' && c <= '~';
    }

    static const char* skip_ansi(const char* p, const char* end)
    {
        if (p == end) return p;
        ++p; // skip ESC
        if (p == end) return p;

        if (*p == '[') {
            ++p;
            while (p < end && !is_control_sequence_terminator(*p))
                ++p;
            if (p < end) ++p; // skip final
        } else {
            ++p; // simple sequence
        }

        return p;
    }

    static std::string strip_ansi(std::string_view v)
    {
        std::string out;
        out.reserve(v.size());

        const char* p   = v.data();
        const char* end = p + v.size();

        while (p < end) {
            if (is_escape_sequence(*p))
                p = skip_ansi(p, end);
            else
                out.push_back(*p++);
        }

        return out;
    }
} // namespace ansi
