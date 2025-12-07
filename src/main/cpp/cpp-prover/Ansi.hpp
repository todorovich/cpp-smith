#pragma once
#include <string>
#include <string_view>

namespace ansi
{
    inline constexpr std::string default_fg  = "\x1b[39m";
    inline constexpr std::string default_bg  = "\x1b[49m";
    inline constexpr std::string reset       = "\x1b[0m";

    inline constexpr std::string black       = "\x1b[30m";
    inline constexpr std::string red         = "\x1b[31m";
    inline constexpr std::string green       = "\x1b[32m";
    inline constexpr std::string yellow      = "\x1b[33m";
    inline constexpr std::string blue        = "\x1b[34m";
    inline constexpr std::string magenta     = "\x1b[35m";
    inline constexpr std::string cyan        = "\x1b[36m";
    inline constexpr std::string white       = "\x1b[37m";

    inline constexpr std::string bright_black   = "\x1b[90m";
    inline constexpr std::string bright_red     = "\x1b[91m";
    inline constexpr std::string bright_green   = "\x1b[92m";
    inline constexpr std::string bright_yellow  = "\x1b[93m";
    inline constexpr std::string bright_blue    = "\x1b[94m";
    inline constexpr std::string bright_magenta = "\x1b[95m";
    inline constexpr std::string bright_cyan    = "\x1b[96m";
    inline constexpr std::string bright_white   = "\x1b[97m";

    inline constexpr std::string bg_black       = "\x1b[40m";
    inline constexpr std::string bg_red         = "\x1b[41m";
    inline constexpr std::string bg_green       = "\x1b[42m";
    inline constexpr std::string bg_yellow      = "\x1b[43m";
    inline constexpr std::string bg_blue        = "\x1b[44m";
    inline constexpr std::string bg_magenta     = "\x1b[45m";
    inline constexpr std::string bg_cyan        = "\x1b[46m";
    inline constexpr std::string bg_white       = "\x1b[47m";

    inline constexpr std::string bg_bright_black   = "\x1b[100m";
    inline constexpr std::string bg_bright_red     = "\x1b[101m";
    inline constexpr std::string bg_bright_green   = "\x1b[102m";
    inline constexpr std::string bg_bright_yellow  = "\x1b[103m";
    inline constexpr std::string bg_bright_blue    = "\x1b[104m";
    inline constexpr std::string bg_bright_magenta = "\x1b[105m";
    inline constexpr std::string bg_bright_cyan    = "\x1b[106m";
    inline constexpr std::string bg_bright_white   = "\x1b[107m";

    inline constexpr std::string bold          = "\x1b[1m";
    inline constexpr std::string dim           = "\x1b[2m";
    inline constexpr std::string italic        = "\x1b[3m";
    inline constexpr std::string underline     = "\x1b[4m";
    inline constexpr std::string blink         = "\x1b[5m";
    inline constexpr std::string reverse       = "\x1b[7m";
    inline constexpr std::string hidden        = "\x1b[8m";
    inline constexpr std::string strikethrough = "\x1b[9m";

    inline constexpr std::string normal        = "\x1b[22m";
    inline constexpr std::string not_italic    = "\x1b[23m";
    inline constexpr std::string not_underline = "\x1b[24m";
    inline constexpr std::string not_blink     = "\x1b[25m";
    inline constexpr std::string not_reverse   = "\x1b[27m";
    inline constexpr std::string not_hidden    = "\x1b[28m";
    inline constexpr std::string not_strike    = "\x1b[29m";

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

    static std::string strip_ansi(const std::string& dirty)
    {
        std::string clean;
        clean.reserve(dirty.size());

        const char* s = dirty.data();
        const char* e = s + dirty.size();

        while (s < e)
        {
            if (*s == '\x1B') {        // ESC
                s++;

                if (s < e && *s == '[') {
                    s++;
                    while (s < e && !((*s >= '@' && *s <= '~')))
                        s++;
                    if (s < e) s++;
                }
                else {
                    if (s < e) s++;
                }
            }
            else {
                clean.push_back(*s++);
            }
        }

        return clean;
    }
} // namespace ansi
