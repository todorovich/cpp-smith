#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct ParseSystemIncludes final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::ParseSystemIncludesFault";
		const std::string& exceptionName() const override { return name; }
	};
}