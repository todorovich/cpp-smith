#pragma once
#include <stdexcept>

namespace cpp_smith
{
    struct SourceGraphError : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    struct FileOpenError final : public SourceGraphError
    {
        using SourceGraphError::SourceGraphError;
    };

    struct IncludeCycleError final : public SourceGraphError
    {
        using SourceGraphError::SourceGraphError;
    };

    class UnresolvedIncludeError final : public SourceGraphError
    {
        using SourceGraphError::SourceGraphError;
    };
}
