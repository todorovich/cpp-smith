#pragma once

#include <format>

namespace test
{
	enum class FailureKind
	{
		Assertion,
		Fault,
		StdException,
		Unknown
	};
}

template <>
struct std::formatter<test::FailureKind>
{
	static constexpr auto parse(std::format_parse_context const& ctx) { return ctx.begin(); }

	static auto format(const test::FailureKind& kind, std::format_context& ctx)
	{
		std::string_view name;
		switch(kind)
		{
			using enum test::FailureKind;
			case Assertion:
				name = "Assertion";
				break;
			case Fault:
				name = "Fault";
				break;
			case StdException:
				name = "StdException";
				break;
			case Unknown:
				name = "Unknown";
				break;
			default:
				name = "Unknown";
				break;
		}
		return std::format_to(ctx.out(), "{}", name);
	}
};