#pragma once

#include "faults/Fault.hpp"

namespace faults::invalid
{
	struct Argument final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::InvalidArgumentFault";
		const std::string& exceptionName() const override { return name; }
	};
}
