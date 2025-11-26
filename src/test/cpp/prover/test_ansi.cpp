#include "Test.hpp"

#include "cpp-prover/Ansi.hpp"

#include <print>

using namespace prover;

static Test<void> test(
    "Test ANSI Color Formatting",
    []()->void
    {
        Assert::areEqual<std::string>(ansi::reset,      "\x1b[0m",  "reset code mismatch");
        Assert::areEqual<std::string>(ansi::default_fg, "\x1b[39m", "default_fg code mismatch");
        Assert::areEqual<std::string>(ansi::default_bg, "\x1b[49m", "default_bg code mismatch");

        // Standard colors
        Assert::areEqual<std::string>(ansi::black,   "\x1b[30m", "black code mismatch");
        Assert::areEqual<std::string>(ansi::red,     "\x1b[31m", "red code mismatch");
        Assert::areEqual<std::string>(ansi::green,   "\x1b[32m", "green code mismatch");
        Assert::areEqual<std::string>(ansi::yellow,  "\x1b[33m", "yellow code mismatch");
        Assert::areEqual<std::string>(ansi::blue,    "\x1b[34m", "blue code mismatch");
        Assert::areEqual<std::string>(ansi::magenta, "\x1b[35m", "magenta code mismatch");
        Assert::areEqual<std::string>(ansi::cyan,    "\x1b[36m", "cyan code mismatch");
        Assert::areEqual<std::string>(ansi::white,   "\x1b[37m", "white code mismatch");

        // Bright colors
        Assert::areEqual<std::string>(ansi::bright_black,   "\x1b[90m", "bright_black code mismatch");
        Assert::areEqual<std::string>(ansi::bright_red,     "\x1b[91m", "bright_red code mismatch");
        Assert::areEqual<std::string>(ansi::bright_green,   "\x1b[92m", "bright_green code mismatch");
        Assert::areEqual<std::string>(ansi::bright_yellow,  "\x1b[93m", "bright_yellow code mismatch");
        Assert::areEqual<std::string>(ansi::bright_blue,    "\x1b[94m", "bright_blue code mismatch");
        Assert::areEqual<std::string>(ansi::bright_magenta, "\x1b[95m", "bright_magenta code mismatch");
        Assert::areEqual<std::string>(ansi::bright_cyan,    "\x1b[96m", "bright_cyan code mismatch");
        Assert::areEqual<std::string>(ansi::bright_white,   "\x1b[97m", "bright_white code mismatch");

    }
);

static prover::Test<void> test_color_function(
    "Test ANSI Color Function",
    []() -> void
    {
        using std::string;

        auto check = [&](std::string_view code, std::string_view name)->std::string
        {
            // expected = <code> + text + <default_fg>
            const std::string expected =
                std::string(code) +
                std::string(name) +
                std::string(ansi::default_fg);

            const std::string actual = ansi::Color(code, name);

            Assert::areEqual<string>(
                expected,
                actual,
                std::string("Color(") + std::string(name) + ") mismatch"
            );

            return actual;
        };


        // Foreground default + normal colors
        std::string multiple_colors_concatenated;
        multiple_colors_concatenated += check(ansi::default_fg, "default_fg");
        multiple_colors_concatenated += " " + check(ansi::black,      "black");
        multiple_colors_concatenated += " " + check(ansi::red,        "red");
        multiple_colors_concatenated += " " + check(ansi::green,      "green");
        multiple_colors_concatenated += " " + check(ansi::yellow,     "yellow");
        multiple_colors_concatenated += " " + check(ansi::blue,       "blue");
        multiple_colors_concatenated += " " + check(ansi::magenta,    "magenta");
        multiple_colors_concatenated += " " + check(ansi::cyan,       "cyan");
        multiple_colors_concatenated += " " + check(ansi::white,      "white");

        // Bright foreground colors
        multiple_colors_concatenated += " " + check(ansi::bright_black,   "bright_black");
        multiple_colors_concatenated += " " + check(ansi::bright_red,     "bright_red");
        multiple_colors_concatenated += " " + check(ansi::bright_green,   "bright_green");
        multiple_colors_concatenated += " " + check(ansi::bright_yellow,  "bright_yellow");
        multiple_colors_concatenated += " " + check(ansi::bright_blue,    "bright_blue");
        multiple_colors_concatenated += " " + check(ansi::bright_magenta, "bright_magenta");
        multiple_colors_concatenated += " " + check(ansi::bright_cyan,    "bright_cyan");
        multiple_colors_concatenated += " " + check(ansi::bright_white,   "bright_white");

        std::println("{}", multiple_colors_concatenated);
    }
);

// Background test in the same style
static prover::Test<void> test_background_function(
    "Test ANSI Background Function",
    []() -> void
    {
        using std::string;

        auto check = [&](std::string_view code, std::string_view name) -> std::string
        {
            const std::string expected =
                std::string(code) +
                std::string(name) +
                std::string(ansi::default_bg);

            const std::string actual = ansi::Background(code, name);

            Assert::areEqual<string>(
                expected,
                actual,
                std::string("Background(") + std::string(name) + ") mismatch"
            );

            return actual;
        };

        std::string multiple_bgs_concatenated;
        multiple_bgs_concatenated += check(ansi::default_bg, "default_bg");
        multiple_bgs_concatenated += " " + check(ansi::bg_black,   "bg_black");
        multiple_bgs_concatenated += " " + check(ansi::bg_red,     "bg_red");
        multiple_bgs_concatenated += " " + check(ansi::bg_green,   "bg_green");
        multiple_bgs_concatenated += " " + check(ansi::bg_yellow,  "bg_yellow");
        multiple_bgs_concatenated += " " + check(ansi::bg_blue,    "bg_blue");
        multiple_bgs_concatenated += " " + check(ansi::bg_magenta, "bg_magenta");
        multiple_bgs_concatenated += " " + check(ansi::bg_cyan,    "bg_cyan");
        multiple_bgs_concatenated += " " + check(ansi::bg_white,   "bg_white");

        multiple_bgs_concatenated += " " + check(ansi::bg_bright_black,   "bg_bright_black");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_red,     "bg_bright_red");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_green,   "bg_bright_green");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_yellow,  "bg_bright_yellow");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_blue,    "bg_bright_blue");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_magenta, "bg_bright_magenta");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_cyan,    "bg_bright_cyan");
        multiple_bgs_concatenated += " " + check(ansi::bg_bright_white,   "bg_bright_white");

        std::println("{}", multiple_bgs_concatenated);
    }
);

static prover::Test<void> test_style_function(
    "Test ANSI Style Function",
    []() -> void
    {
        using std::string;

        auto check = [&](std::string_view attr, std::string_view name) -> std::string
        {
            const std::string expected =
                std::string(attr) +
                std::string(name) +
                std::string(ansi::StyleEnd(attr));

            const std::string actual = ansi::Style(attr, name);

            Assert::areEqual<string>(
                expected,
                actual,
                std::string("Style(") + std::string(name) + ") mismatch"
            );

            return actual;
        };

        std::string multiple_styles_concatenated;
        multiple_styles_concatenated += check(ansi::bold,          "bold");
        multiple_styles_concatenated += " " + check(ansi::dim,           "dim");
        multiple_styles_concatenated += " " + check(ansi::italic,        "italic");
        multiple_styles_concatenated += " " + check(ansi::underline,     "underline");
        multiple_styles_concatenated += " " + check(ansi::blink,         "blink");
        multiple_styles_concatenated += " " + check(ansi::reverse,       "reverse");
        multiple_styles_concatenated += " " + check(ansi::hidden,        "hidden");
        multiple_styles_concatenated += " " + check(ansi::strikethrough, "strikethrough");

        std::println("{}", multiple_styles_concatenated);
    }
);

static prover::Test<void> test_nested_composition(
    "Test ANSI Nested Composition",
    []() -> void
    {
        using std::string;
        using namespace ansi;

        const string text = "Composition Test";

        const std::string expected =
            std::string(ansi::bold) +
            std::string(ansi::green) +
            std::string(ansi::bg_black) +
            std::string(ansi::italic) +
            std::string(ansi::strikethrough) +
            std::string(ansi::underline) +
            std::string(text) +
            std::string(ansi::not_underline) +
            std::string(ansi::not_strike) +
            std::string(ansi::not_italic) +
            std::string(ansi::default_bg) +
            std::string(ansi::default_fg) +
            std::string(ansi::normal);


        const string actual = Style(
            ansi::bold,
            Color(
                ansi::green,
                Background(
                    ansi::bg_black,
                    Style(
                        ansi::italic,
                        Style(
                            ansi::strikethrough,
                            Style(ansi::underline, text)
                        )
                    )
                )
            )
        );

        Assert::areEqual<string>(
            expected,
            actual,
            "Nested Style(...) composition mismatch"
        );

        std::println("{}", actual);
    }
);

