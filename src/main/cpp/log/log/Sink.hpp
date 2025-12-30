#pragma once

#include "LogMessageFormatter.hpp"

namespace logging
{
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
}