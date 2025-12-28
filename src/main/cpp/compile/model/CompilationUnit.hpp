#pragma once

#include <utility>
#include <algorithm>

#include "Configuration.hpp"
#include "SourceFile.hpp"

namespace cpp_smith
{
    class CompilationUnit
    {
        SourceFile _source;
        Configuration _configuration;

    public:
        CompilationUnit(SourceFile&& source, Configuration configuration)
            : _source(source)
            , _configuration(std::move(configuration))
        {}

        [[nodiscard]] const SourceFile& getSourceFile() const { return _source; }

        [[nodiscard]] const Configuration& getConfiguration() const { return _configuration; }
    };
}
