#pragma once

#include <format>

namespace test
{
	enum class TestStatus { Skipped = -1, Passed = 0, Failed = 1 };
}

template <>
struct std::formatter<test::TestStatus>
{
	static constexpr auto parse(const std::format_parse_context& ctx) { return ctx.begin(); }

	static auto format(const test::TestStatus& status, std::format_context& ctx)
	{
		std::string_view name;
		switch(status)
		{
			using enum test::TestStatus;
			case Skipped:
				name = "Skipped";
				break;
			case Passed:
				name = "Passed";
				break;
			case Failed:
				name = "Failed";
				break;
			default:
				name = "Unknown";
				break;
		}
		return std::format_to(ctx.out(), "{}", name);
	}
};