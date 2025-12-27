#pragma once

#include <string>

#include "LogMessage.hpp"

namespace logging
{
    struct LogMessageFormatter
    {
        virtual ~LogMessageFormatter() = default;
        virtual std::string format(const LogMessage&) = 0;
    };

    struct MinimalFormatter final : LogMessageFormatter
    {
        using LogMessageFormatter::LogMessageFormatter;

        std::string format(const LogMessage& logMessage) override {
            return logMessage.message;
        }
    };
}
