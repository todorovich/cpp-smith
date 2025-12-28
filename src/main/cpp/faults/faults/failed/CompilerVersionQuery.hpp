#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct CompilerVersionQuery final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::CompilerVersionQueryFault";
		const std::string& exceptionName() const override { return name; }
	};
}