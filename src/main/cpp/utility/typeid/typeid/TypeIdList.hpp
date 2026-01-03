#pragma once

#include <array>
#include <cstddef>
#include <initializer_list>
#include <string_view>

#include "TypeId.hpp"

namespace cpp_smith
{
	inline constexpr std::size_t TypeIdListMax = 7;

	class TypeIdList final
	{
		std::array<TypeId, TypeIdListMax> _ids{};
		std::size_t _size{0};

		constexpr void add_unique_unchecked(TypeId id) noexcept
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if (_ids[i] == id) return;
			}
			_ids[_size++] = id;
		}

	public:
		constexpr TypeIdList() noexcept = default;

		constexpr TypeIdList(std::initializer_list<TypeId> ids) noexcept
		{
			for (TypeId id : ids)
			{
				(void)try_add_unique(id);
			}
		}

		constexpr bool try_add_unique(TypeId id) noexcept
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if (_ids[i] == id) return true; // already present
			}
			if (_size >= TypeIdListMax) return false;
			_ids[_size++] = id;
			return true;
		}

		[[nodiscard]] constexpr bool contains(TypeId id) const noexcept
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if (_ids[i] == id) return true;
			}
			return false;
		}

		[[nodiscard]] constexpr bool empty() const noexcept { return _size == 0; }
		[[nodiscard]] constexpr std::size_t size() const noexcept { return _size; }

		[[nodiscard]] constexpr TypeId at(std::size_t i) const noexcept { return _ids[i]; }

		friend constexpr bool operator==(const TypeIdList&, const TypeIdList&) noexcept = default;
	};

	[[nodiscard]] constexpr TypeIdList operator&&(TypeId a, TypeId b) noexcept
	{
		TypeIdList out{};
		(void)out.try_add_unique(a);
		(void)out.try_add_unique(b);
		return out;
	}

	[[nodiscard]] constexpr TypeIdList operator&&(const TypeIdList& types, TypeId t) noexcept
	{
		TypeIdList out = types;
		(void)out.try_add_unique(t);
		return out;
	}

	[[nodiscard]] constexpr TypeIdList operator&&(TypeId t, const TypeIdList& types) noexcept
	{
		return types && t;
	}

	[[nodiscard]] constexpr TypeIdList operator&&(const TypeIdList& left, const TypeIdList& right) noexcept
	{
		TypeIdList out = left;
		for (std::size_t j = 0; j < right.size(); ++j) (void)out.try_add_unique(right.at(j));
		return out;
	}

	template <>
	struct TypeKey<TypeIdList>
	{
		static constexpr std::string_view value = "cpp_smith::TypeIdList";
	};
}