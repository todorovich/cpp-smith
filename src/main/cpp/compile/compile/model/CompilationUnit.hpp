#pragma once

#include <utility>
#include <algorithm>

#include "CompilationConfiguration.hpp"
#include "SourceFile.hpp"

namespace cpp_smith
{
    class CompilationUnit
    {
        SourceFile _source;
        CompilationConfiguration _configuration;

    public:
        CompilationUnit(SourceFile&& source, CompilationConfiguration configuration)
            : _source(source)
            , _configuration(std::move(configuration))
        {}

        [[nodiscard]] const SourceFile& getSourceFile() const { return _source; }

        [[nodiscard]] const CompilationConfiguration& getConfiguration() const { return _configuration; }
    };
}
