#pragma once

#include <string_view>
#include <cstddef>

namespace cpp_smith
{
	template <class T>struct TypeKey;

	template <> struct TypeKey<void> { static constexpr std::string_view value = "void"; };
	template <> struct TypeKey<std::nullptr_t> { static constexpr std::string_view value = "std::nullptr_t"; };

	template <> struct TypeKey<bool> { static constexpr std::string_view value = "bool"; };

	template <> struct TypeKey<char> { static constexpr std::string_view value = "char"; };
	template <> struct TypeKey<signed char> { static constexpr std::string_view value = "signed char"; };
	template <> struct TypeKey<unsigned char> { static constexpr std::string_view value = "unsigned char"; };

	template <> struct TypeKey<wchar_t> { static constexpr std::string_view value = "wchar_t"; };
	template <> struct TypeKey<char8_t> { static constexpr std::string_view value = "char8_t"; };
	template <> struct TypeKey<char16_t> { static constexpr std::string_view value = "char16_t"; };
	template <> struct TypeKey<char32_t> { static constexpr std::string_view value = "char32_t"; };

	template <> struct TypeKey<short> { static constexpr std::string_view value = "short"; };
	template <> struct TypeKey<unsigned short> { static constexpr std::string_view value = "unsigned short"; };

	template <> struct TypeKey<int> { static constexpr std::string_view value = "int"; };
	template <> struct TypeKey<unsigned int> { static constexpr std::string_view value = "unsigned int"; };

	template <> struct TypeKey<long> { static constexpr std::string_view value = "long"; };
	template <> struct TypeKey<unsigned long> { static constexpr std::string_view value = "unsigned long"; };

	template <> struct TypeKey<long long> { static constexpr std::string_view value = "long long"; };
	template <> struct TypeKey<unsigned long long> { static constexpr std::string_view value = "unsigned long long"; };

	template <> struct TypeKey<float> { static constexpr std::string_view value = "float"; };
	template <> struct TypeKey<double> { static constexpr std::string_view value = "double"; };
	template <> struct TypeKey<long double> { static constexpr std::string_view value = "long double"; };
}