#pragma once

#include <cstdint>
#include <algorithm>

namespace cpp_smith
{
	class ArtifactType final
	{
		template <class T>
		inline static std::uint8_t type_anchor = 0;

		const void* id { nullptr };

		constexpr explicit ArtifactType(const void* p) noexcept
			: id(p)
		{}

	  public:
		friend constexpr bool operator==(ArtifactType, ArtifactType) noexcept = default;

		constexpr const void* getId() const noexcept { return id; }

		template <class T>
		static constexpr ArtifactType of() noexcept
		{
			return ArtifactType{ &type_anchor<T> };
		}
	};
}

namespace std
{
	template <>
	struct hash<cpp_smith::ArtifactType>
	{
		size_t operator()(const cpp_smith::ArtifactType artifactType) const noexcept
		{
			return std::hash<const void*>{}(artifactType.getId());
		}
	};
}