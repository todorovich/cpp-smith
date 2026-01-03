#pragma once

#include "faults/Fault.hpp"

namespace faults::failed
{
	struct FileSystem final : Fault
	{
		using Fault::Fault;
		inline static const std::string name = "faults::failed::FileSystemFault";
		const std::string& exceptionName() const override { return name; }
	};
}