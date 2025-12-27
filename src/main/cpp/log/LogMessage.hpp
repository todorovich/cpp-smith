#pragma once

#include <string>
#include <chrono>
#include <thread>

namespace logging
{
	struct LogMessage
	{
		std::string message;
		std::string scope;
		enum class Level { Trace, Debug, Info, Warn, Error, Critical } level;
		std::chrono::system_clock::time_point timestamp;
		std::thread::id thread_id;
	};
}