#pragma once

#include <cstddef>
#include <format>
#include <functional>
#include <string>

namespace cpp_smith
{
	struct SymanticVersion
	{
		int major;
		int minor;
		int patch;

		friend bool operator==(const SymanticVersion&, const SymanticVersion&) = default;
	};

	struct ProjectCoordinates final
	{
		// TODO validation for each, maybe make a wrapper for string that validates.
		std::string group;  // I like java style net.todorovich.package but i should really work this out
		std::string project; // Just a name? no special characters?
		SymanticVersion version; // Maybe force symantic versions?

		ProjectCoordinates(
			const std::string_view group,
			const std::string_view project,
			const SymanticVersion& version
		)
			: group(group)
			, project(project)
			, version(version)
		{}

		friend bool operator==(const ProjectCoordinates&, const ProjectCoordinates&) = default;

		[[nodiscard]] std::string toString(const char sep = ':') const;
	};
}

namespace std
{
	template <>
	struct formatter<cpp_smith::SymanticVersion, char>
	{
		constexpr auto parse(std::format_parse_context& ctx)
		{
			const auto it = ctx.begin();
			if(it != ctx.end() && *it != '}')
				throw std::format_error("SymanticVersion does not support format specifiers");
			return it;
		}

		template <class FormatContext>
		auto format(const cpp_smith::SymanticVersion& v, FormatContext& ctx) const
		{
			return std::format_to(ctx.out(), "{}.{}.{}", v.major, v.minor, v.patch);
		}
	};

	template <>
	struct hash<cpp_smith::ProjectCoordinates>
	{
		size_t operator()(const cpp_smith::ProjectCoordinates& c) const noexcept
		{
			auto h          = std::hash<std::string>{}(c.group);
			auto mix_string = [&](const std::string& s)
			{
				h ^= std::hash<std::string>{}(s) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
			};
			auto mix_int = [&](int val)
			{
				h ^= std::hash<int>{}(val) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
			};

			mix_string(c.project);
			mix_int(c.version.major);
			mix_int(c.version.minor);
			mix_int(c.version.patch);
			return h;
		}
	};

	template <>
	struct formatter<cpp_smith::ProjectCoordinates, char> : formatter<std::string_view, char>
	{
		constexpr auto parse(std::format_parse_context& ctx)
		{
			// Accept only "{}" (no format specifiers)
			const auto it = ctx.begin();
			if (it != ctx.end() && *it != '}')
				throw std::format_error("ProjectCoordinates does not support format specifiers");
			return it;
		}

		template <class FormatContext>
		auto format(const cpp_smith::ProjectCoordinates& value, FormatContext& ctx) const
		{
			const std::string s = value.toString(); // default ':' separator
			return formatter<std::string_view, char>::format(std::string_view{s}, ctx);
		}
	};
}

inline std::string cpp_smith::ProjectCoordinates::toString(const char sep) const {
	return std::format("{}{}{}{}{}", group, sep, project, sep, version);
}