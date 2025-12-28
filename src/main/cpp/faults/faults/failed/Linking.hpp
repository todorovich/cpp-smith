#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct Linking final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::LinkingFault";
		const std::string& exceptionName() const override { return name; }
	};
}