#pragma once

#include <source_location>
#include <stacktrace>

namespace faults
{
	struct Fault : std::exception
	{
		const std::string message;
		const std::source_location source_location;
		const std::stacktrace stacktrace;

		explicit Fault(
			const std::string& message,
			const std::source_location sourceLocation = std::source_location::current(),
			const std::stacktrace& stackTrace = std::stacktrace::current()
		) noexcept
			: message(std::move(message))
			, source_location(sourceLocation)
			, stacktrace(stackTrace)
		{};

		explicit Fault(
			std::string&& message,
			const std::source_location sourceLocation = std::source_location::current(),
			const std::stacktrace& stackTrace = std::stacktrace::current()
		) noexcept
			: message(std::move(message))
			, source_location(sourceLocation)
			, stacktrace(stackTrace)
		{};

		Fault(Fault&& other) noexcept = default;
		Fault(const Fault& other) noexcept = default;
		~Fault() noexcept override = default;

		Fault& operator=(Fault&& other) noexcept      = delete;
		Fault& operator=(const Fault& other) noexcept = delete;

		virtual const std::string& exceptionName() const = 0;

		const char* what() const noexcept override
		{
			return this->exceptionName().c_str();
		}
	};
}