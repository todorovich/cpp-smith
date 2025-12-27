#pragma once

#include <chrono>
#include <thread>

#include "LogMessage.hpp"
#include "Sink.hpp"

namespace logging
{
    class Logger {
        std::string _scope;
        std::vector<std::unique_ptr<Sink>> _sinks;

    public:

        Logger() = default;

        template<typename... Sinks>
        explicit Logger(std::string scope, Sinks&&... sinks)
            : _scope(std::move(scope))
        {
            (_sinks.emplace_back(std::move(sinks)), ...);
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        void print(const std::string_view view)
        {
            const LogMessage message {
                .message = std::string{view},
                .scope = _scope,
                .level = LogMessage::Level::Info,
                .timestamp = std::chrono::system_clock::now(),
                .thread_id = std::this_thread::get_id()
            };

            for (const auto& sink : _sinks)
            {
                sink->write(message);
                sink->flush();
            }
        }

        template<typename... Args>
        void print(std::format_string<Args...> fmt, Args&&... args) {
            const LogMessage message {
                .message = std::format(fmt, std::forward<Args>(args)...),
                .scope = _scope,
                .level = LogMessage::Level::Info,
                .timestamp = std::chrono::system_clock::now(),
                .thread_id = std::this_thread::get_id()
            };

            for (const auto& sink : _sinks)
            {
                sink->write(message);
                sink->flush();
            }
        }

        std::string_view getScope() const { return _scope; };
    };
}

