#pragma once

#include <cstdint>
#include <string_view>
#include <functional>
#include <concepts>

#include "TypeKey.hpp"

namespace cpp_smith
{
	namespace detail
	{
		constexpr std::uint64_t fnv1a_64(std::string_view s) noexcept
		{
			std::uint64_t hash = 14695981039346656037ull;
			for (const char character : s)
			{
				hash ^= static_cast<unsigned char>(character);
				hash *= 1099511628211ull;
			}
			return hash;
		}

		template <class T>
		concept HasTypeKey = requires {
			{ TypeKey<T>::value } -> std::convertible_to<std::string_view>;
		};
	}

	class TypeId final
	{
		std::uint64_t _id { 0 };

		consteval explicit TypeId(std::uint64_t v) noexcept
			: _id(v)
		{}

	public:
		consteval TypeId() noexcept = default;

		friend constexpr bool operator==(TypeId, TypeId) noexcept = default;

		[[nodiscard]] constexpr std::uint64_t value() const noexcept { return _id; }

		static consteval TypeId fromKey(const std::string_view stableKey) noexcept
		{
			return TypeId{ detail::fnv1a_64(stableKey) };
		}

		template <class T>
		static consteval TypeId of() noexcept
		{
			static_assert(
				detail::HasTypeKey<T>,
				"cpp_smith::TypeId::of<T>() requires a stable key. Specialize cpp_smith::TypeKey<T>."
			);

			constexpr std::string_view key = TypeKey<T>::value;
			static_assert(!key.empty(), "cpp_smith::TypeKey<T>::value must not be empty.");
			return fromKey(key);
		}
	};

	template <>
	struct TypeKey<TypeId>
	{
		static constexpr std::string_view value = "cpp_smith::TypeId";
	};
}

namespace std
{
	template <>
	struct hash<cpp_smith::TypeId>
	{
		size_t operator()(const cpp_smith::TypeId t) const noexcept
		{
			return std::hash<std::uint64_t>{}(t.value());
		}
	};
}