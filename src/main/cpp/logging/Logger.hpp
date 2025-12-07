#pragma once

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

    class Sink
    {
    protected:
        std::unique_ptr<LogMessageFormatter> _formatter;

    public:
        explicit Sink(std::unique_ptr<LogMessageFormatter> fmt)
            : _formatter(std::move(fmt))
        {}

        Sink(const Sink&) = delete;
        Sink(Sink&& sink) = default;
        virtual ~Sink() = default;

        Sink& operator=(const Sink&) = delete;
        Sink& operator=(Sink&& sink) = default;

        virtual void doWrite(std::string_view) = 0;

        void write(const LogMessage& msg)
        {
            doWrite(_formatter->format(msg));
        }

        virtual void flush() {}
    };

    class ConsoleSink final : public Sink {
    public:
        using Sink::Sink;

        void doWrite(const std::string_view view) override
        {
            std::fwrite(view.data(), sizeof(char), view.size(), stdout);
        }
    };

    class StringSink final : public Sink
    {
        std::string& _buffer;

    public:
        StringSink(std::unique_ptr<LogMessageFormatter> formatter,
                   std::string& buffer)
            : Sink(std::move(formatter))
            , _buffer(buffer)
        {}

        StringSink(const StringSink&) = delete;
        StringSink& operator=(const StringSink&) = delete;

        StringSink(StringSink&&) = default;
        StringSink& operator=(StringSink&&) = delete;

        void doWrite(const std::string_view view) override
        {
            _buffer.append(view);
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        void clear()
        {
            _buffer.clear();
        }
    };

    class FileSink final : public Sink {
        std::FILE* _file;
    public:
        FileSink(std::unique_ptr<LogMessageFormatter> fmt, const std::string& path)
            : Sink(std::move(fmt))
            , _file(std::fopen(path.c_str(), "w"))
        {}

        ~FileSink() override
        {
            if (_file) std::fclose(_file);
        }

        void doWrite(const std::string_view view) override
        {
            std::fwrite(view.data(), 1, view.size(), _file);
        }

        void flush() override
        {
            std::fflush(_file);
        }
    };


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

