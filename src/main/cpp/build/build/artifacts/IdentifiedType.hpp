#pragma once

#include <cassert>
#include <source_location>
#include <print>

#include "TypeIdList.hpp"
#include "test/Assert.hpp"


namespace cpp_smith
{
	class IdentifiedType
	{
		TypeIdList _types;

	  protected:
		explicit IdentifiedType(const TypeId type)
			: _types({type})
		{}

		explicit IdentifiedType(TypeIdList types)
			: _types(types)
		{}

		explicit IdentifiedType(int _cpp_par_);

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
			// TODO make this work?
			if constexpr (is<T>())
			{

			}
			else
			{

			}

			assert(is<T>() && "IdentifiedType::as<T>() called with wrong type");
			return static_cast<T&>(*this);
		}

		template <class T>
		[[nodiscard]] const T& as(const std::source_location sourceLocation = {}) const& noexcept
		{
			assert(is<T>() && "IdentifiedType::as<T>() called with wrong type");
			return static_cast<const T&>(*this);
		}
	};
}
