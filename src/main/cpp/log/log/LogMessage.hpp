#pragma once

#include <string>
#include <chrono>
#include <thread>

namespace logging
{
	struct LogMessage
	{
		enum class Level { Trace, Debug, Info, Warn, Error, Critical };

		std::string message;
		std::string scope;
		Level level;
		std::chrono::system_clock::time_point timestamp;
		std::thread::id thread_id;
	};
}