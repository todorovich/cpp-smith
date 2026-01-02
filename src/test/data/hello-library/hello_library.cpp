#include "hello_library.hpp"

#include <print>

void hello_library::print(std::string_view string)
{
	return std::print("{}", string);
}
