#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "faults/Fault.hpp"

namespace faults::invalid
{
	struct CircularDependency final : Fault
	{
		// Indices (into the input span at the time of analysis) that are in, or blocked by, cycles.
		std::vector<std::size_t> cycle_indices;

		explicit CircularDependency(
			std::string message,
			std::vector<std::size_t> cycleIndices
		) noexcept
			: Fault(std::move(message))
			, cycle_indices(std::move(cycleIndices))
		{}

		inline static const std::string name = "faults::invalid::CircularDependency";
		const std::string& exceptionName() const override { return name; }
	};
}
