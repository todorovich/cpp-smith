#pragma once

#include "faults/Fault.hpp"

namespace faults::unsupported
{
	struct CompilerVersion final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::unsupported::CompilerVersion";
		const std::string& exceptionName() const override { return name; }
	};
}
