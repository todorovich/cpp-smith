#pragma once

#include <string>
#include <chrono>

namespace test
{
	struct FormatHelper
	{
		FormatHelper() = delete;

		static std::string indent_multiline(const std::string_view s, const std::string_view indent)
		{
			std::string out;
			out.reserve(s.size() + 16);

			bool at_line_start = false; // we only indent after a newline
			for (char ch : s)
			{
				if (at_line_start)
				{
					out.append(indent);
					at_line_start = false;
				}
				out.push_back(ch);
				if (ch == '\n')
					at_line_start = true;
			}
			return out;
		}

		static std::string formatDuration(const std::chrono::nanoseconds nanoseconds)
		{
			if(nanoseconds.count() < 1'000)
			{
				return std::format(
					"{:.2f} ns",
					static_cast<double>(nanoseconds.count())
				);
			}
			if(nanoseconds.count() < 1'000'000)
			{
				return std::format(
					"{:.2f} μs",
					static_cast<long double>(nanoseconds.count()) / 1'000.0
				);
			}
			if(nanoseconds.count() < 1'000'000'000)
			{
				return std::format(
					"{:.2f} ms",
					static_cast<long double>(nanoseconds.count()) / 1'000'000.0
				);
			}
			if(nanoseconds.count() < 60'000'000'000)
			{
				return std::format(
					"{:.2f} s",
					static_cast<long double>(nanoseconds.count()) / 1'000'000'000.0
				);
			}
			if(nanoseconds.count() < 3'600'000'000'000)
			{
				return std::format(
					"{:.2f} m",
					static_cast<long double>(nanoseconds.count()) / 60'000'000'000.0
				);
			}

			return std::format(
				"{:.2f} h",
				static_cast<long double>(nanoseconds.count()) / 3'600'000'000'000.0
			);
		}
	};
}
