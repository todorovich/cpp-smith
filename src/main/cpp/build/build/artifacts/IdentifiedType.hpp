#pragma once

#include <cassert>
#include <source_location>

#include "TypeIdList.hpp"
#include "faults/faults.hpp"
#include "test/Assert.hpp"

namespace cpp_smith
{
	class IdentifiedType
	{
		TypeIdList _types;

	protected:
		constexpr explicit IdentifiedType(const TypeId& type)
			: _types(TypeIdList{type})
		{}

		constexpr explicit IdentifiedType(const TypeIdList& types)
			: _types(types)
		{}

	public:
		[[nodiscard]] TypeIdList getTypes() const noexcept { return _types; }

		[[nodiscard]] bool is(const TypeId type) const noexcept
		{
			return _types.contains(type);
		}

		template <class T>
		[[nodiscard]] bool is() const noexcept { return is(TypeId::of<T>()); }

		template <class T>
		[[nodiscard]] T& as(const std::source_location sourceLocation = std::source_location::current()) & noexcept
		{
			if (is<T>())
			{
				return static_cast<T&>(*this);
			}

			throw faults::unsupported::Cast("Unable to cast to type T.");
		}

		template <class T>
		[[nodiscard]] const T& as(const std::source_location sourceLocation = {}) const& noexcept
		{
			assert(is<T>() && "IdentifiedType::as<T>() called with wrong type");
			return static_cast<const T&>(*this);
		}
	};
}