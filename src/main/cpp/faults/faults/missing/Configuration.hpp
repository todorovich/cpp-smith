#pragma once

#include "faults/Fault.hpp"

namespace faults::missing
{
	struct Configuration final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::missing::NotFoundFault";
		const std::string& exceptionName() const override { return name; }
	};
}
