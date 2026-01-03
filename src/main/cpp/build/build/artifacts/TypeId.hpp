#pragma once

#include <cstdint>
#include <algorithm>

namespace cpp_smith
{
	class TypeId final
	{
		template <class T>
		inline static std::uint8_t type_anchor = 0;

		const void* id { nullptr };

		constexpr explicit TypeId(const void* p) noexcept
			: id(p)
		{}

	  public:
		friend constexpr bool operator==(TypeId, TypeId) noexcept = default;

		constexpr const void* getId() const noexcept { return id; }

		template <class T>
		static constexpr TypeId of() noexcept
		{
			return TypeId{ &type_anchor<T> };
		}
	};
}

namespace std
{
	template <>
	struct hash<cpp_smith::TypeId>
	{
		size_t operator()(const cpp_smith::TypeId artifactType) const noexcept
		{
			return std::hash<const void*>{}(artifactType.getId());
		}
	};
}