#pragma once

#include <cstddef>
#include <functional>
#include <string>

#include "../ProjectCoordinates.hpp"

namespace cpp_smith
{
    struct ArtifactCoordinates final
    {
        ProjectCoordinates projectCoordinates;
        std::string artifact_name;

        ArtifactCoordinates(const ProjectCoordinates& projectCoordinates, const std::string& artifactName)
            : projectCoordinates(projectCoordinates)
            , artifact_name(artifactName)
        {}

        friend bool operator==(const ArtifactCoordinates&, const ArtifactCoordinates&) = default;

        [[nodiscard]] std::string toString(const char sep = ':') const
        {
            return std::format("{}{}{}", projectCoordinates, sep, artifact_name);
        }
    };
}

namespace std
{
    template <>
    struct hash<cpp_smith::ArtifactCoordinates>
    {
        size_t operator()(const cpp_smith::ArtifactCoordinates& c) const noexcept
        {
            auto h = std::hash<cpp_smith::ProjectCoordinates>{}(c.projectCoordinates);
            h ^= std::hash<std::string>{}(c.artifact_name) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
            return h;
        }
    };

    template <>
    struct formatter<cpp_smith::ArtifactCoordinates, char> : formatter<std::string_view, char>
    {
        static constexpr auto parse(const std::format_parse_context& ctx)
        {
            // Accept only "{}" (no format specifiers)
            const auto it = ctx.begin();
            if (it != ctx.end() && *it != '}')
                throw std::format_error("ArtifactCoordinates does not support format specifiers");
            return it;
        }

        template <class FormatContext>
        auto format(const cpp_smith::ArtifactCoordinates& value, FormatContext& ctx) const
        {
            const std::string s = value.toString(); // default ':' separator
            return formatter<std::string_view, char>::format(std::string_view{s}, ctx);
        }
    };
}