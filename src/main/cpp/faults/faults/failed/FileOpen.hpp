#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct FileOpen final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::FileOpenFault";
		const std::string& exceptionName() const override { return name; }
	};
}