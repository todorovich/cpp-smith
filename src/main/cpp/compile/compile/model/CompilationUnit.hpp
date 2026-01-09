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
        const CompilationConfiguration& _configuration;

    public:
        CompilationUnit(SourceFile&& source, const CompilationConfiguration& configuration)
            : _source(std::move(source))
            , _configuration(configuration)
        {}

        [[nodiscard]] const SourceFile& getSourceFile() const { return _source; }

        [[nodiscard]] const CompilationConfiguration& getConfiguration() const { return _configuration; }
    };
}
