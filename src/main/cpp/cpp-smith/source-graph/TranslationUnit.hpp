#pragma once

#include <utility>

#include "configuration/Configuration.hpp"
#include "source-graph/SourceFile.hpp"

namespace cpp_smith
{
    class TranslationUnit
    {
        SourceFile _source;
        Configuration _configuration;
        std::filesystem::path _objectFile = std::filesystem::path{};
        std::filesystem::path _dependencyFile = std::filesystem::path{};

        // TODO: dirty flag? Should check last updated or hash the file and store that when compiling. Check against
        //  that when recompiling. Double check expected output is there and matches hash or version.

    public:
        TranslationUnit(SourceFile&& source, Configuration configuration)
            : _source(source)
            , _configuration(std::move(configuration))
        {
        }

        [[nodiscard]] const SourceFile& getSourceFile() const { return _source; }
        [[nodiscard]] const Configuration& getConfiguration() const { return _configuration; }

        [[nodiscard]] const std::filesystem::path& getObjectFile() const { return _objectFile; }
        [[nodiscard]] const std::filesystem::path& getDependencyFile() const { return _dependencyFile; }

        void setObjectFile(const std::filesystem::path& path)
        {
            _objectFile = path;
        }

        void setDependencyFile(const std::filesystem::path& path)
        {
            _dependencyFile = path;
        }
    };
}
