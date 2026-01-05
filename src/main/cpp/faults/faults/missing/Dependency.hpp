#pragma once

#include <cstddef>
#include <string>

#include "faults/Fault.hpp"

namespace faults::missing
{
	struct Dependency final : Fault
	{
		std::size_t missing_dependencies_count{};
		std::string missing_dependencies_details;

		explicit Dependency(
			std::string message,
			std::size_t missingCount,
			std::string details = {}
		) noexcept
			: Fault(std::move(message))
			, missing_dependencies_count(missingCount)
			, missing_dependencies_details(std::move(details))
		{}

		inline static const std::string name = "faults::missing::Dependency";
		const std::string& exceptionName() const override { return name; }
	};
}
