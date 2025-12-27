#pragma once

#include <cstddef>
#include <functional>
#include <string>

namespace cpp_smith
{
	struct ProjectCoordinates final
	{
		const std::string group;
		const std::string project;
		const std::string version;

		ProjectCoordinates(
			const std::string_view group,
			const std::string_view project,
			const std::string_view version
		)
			: group(group)
			, project(project)
			, version(version)
		{}

		friend bool operator==(const ProjectCoordinates&, const ProjectCoordinates&) = default;

		[[nodiscard]] std::string toString(const char sep = ':') const
		{
			return group + sep + project + sep + version;
		}
	};
}

namespace std
{
	template <>
	struct hash<cpp_smith::ProjectCoordinates>
	{
		size_t operator()(const cpp_smith::ProjectCoordinates& c) const noexcept
		{
			auto h = std::hash<std::string>{}(c.group);
			auto mix = [&](const std::string& s)
			{
				h ^= std::hash<std::string>{}(s) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
			};

			mix(c.project);
			mix(c.version);
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