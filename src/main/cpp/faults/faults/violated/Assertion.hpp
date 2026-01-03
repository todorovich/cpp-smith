#pragma once

#include "../Fault.hpp"

namespace faults::violated
{
	struct Assertion final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::violated::Assertion";
		const std::string& exceptionName() const override { return name; }
	};
}
