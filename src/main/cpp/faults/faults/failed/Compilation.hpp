#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct Compilation final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::failed::CompilationFault";
		const std::string& exceptionName() const override { return name; }
	};
}