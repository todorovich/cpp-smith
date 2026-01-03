#pragma once

#include "faults/Fault.hpp"

namespace faults::unsupported
{
	struct Cast final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::unsupported::Cast";
		const std::string& exceptionName() const override { return name; }
	};
}
