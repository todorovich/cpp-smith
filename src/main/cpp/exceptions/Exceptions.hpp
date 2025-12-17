#pragma once

#include <source_location>
#include <stacktrace>

namespace exceptions
{
    struct CppSmithException : std::exception
    {
        const std::string message;
        const std::source_location source_location;
        const std::stacktrace stacktrace;

        explicit CppSmithException(
            const std::string& message,
            const std::source_location sourceLocation = std::source_location::current(),
            const std::stacktrace& stackTrace = std::stacktrace::current()
        ) noexcept
            : message(std::move(message))
            , source_location(sourceLocation)
            , stacktrace(stackTrace)
        {};

        explicit CppSmithException(
            std::string&& message,
            const std::source_location sourceLocation = std::source_location::current(),
            const std::stacktrace& stackTrace = std::stacktrace::current()
        ) noexcept
            : message(std::move(message))
            , source_location(sourceLocation)
            , stacktrace(stackTrace)
        {};

        CppSmithException(CppSmithException&& other) noexcept = default;
        CppSmithException(const CppSmithException& other) noexcept = default;
        ~CppSmithException() noexcept override = default;

        CppSmithException& operator=(CppSmithException&& other) noexcept      = delete;
        CppSmithException& operator=(const CppSmithException& other) noexcept = delete;

        virtual const std::string& exceptionName() const = 0;

        const char* what() const noexcept override
        {
            return this->exceptionName().c_str();
        }
    };

    struct FileSystemError final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::FileSystemError";
        const std::string& exceptionName() const override { return name; }
    };

    struct UnsupportedCompilerVersion final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::UnsupportedCompilerVersion";
        const std::string& exceptionName() const override { return name; }
    };

    struct InvalidInput final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::InvalidInput";
        const std::string& exceptionName() const override { return name; }
    };

    struct NotFound final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::NotFound";
        const std::string& exceptionName() const override { return name; }
    };

    struct AssertionFailed final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::AssertionFailed";
        const std::string& exceptionName() const override { return name; }
    };

    struct ParseSystemIncludesFailed final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::ParseSystemIncludesFailed";
        const std::string& exceptionName() const override { return name; }
    };

    struct FailedToGetCompilerVersion final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::FailedToGetCompilerVersion";
        const std::string& exceptionName() const override { return name; }
    };

    struct CompilationError final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::CompilationError";
        const std::string& exceptionName() const override { return name; }
    };

    struct LinkingError final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::LinkingError";
        const std::string& exceptionName() const override { return name; }
    };

    struct FileOpenError final : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::FileOpenError";
        const std::string& exceptionName() const override { return name; }
    };

    struct SourceGraphError : CppSmithException
    {
        using CppSmithException::CppSmithException;
        inline static const std::string name = "exceptions::SourceGraphError";
        const std::string& exceptionName() const override { return name; }
    };

    struct IncludeCycleError final : SourceGraphError
    {
        using SourceGraphError::SourceGraphError;
        inline static const std::string name = "exceptions::IncludeCycleError";
        const std::string& exceptionName() const override { return name; }
    };

    struct UnresolvedIncludeError final : SourceGraphError
    {
        using SourceGraphError::SourceGraphError;
        inline static const std::string name = "exceptions::UnresolvedIncludeError";
        const std::string& exceptionName() const override { return name; }
    };
}
