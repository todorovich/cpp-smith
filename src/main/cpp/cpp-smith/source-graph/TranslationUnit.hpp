#pragma once

#include <utility>
#include <filesystem>
#include <algorithm>

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
        std::filesystem::file_time_type _last_write_time_build{};

    public:
        static std::filesystem::file_time_type getLastWriteTime(
            const std::filesystem::path& file
        )
        {
            std::error_code error_code;
            if(!std::filesystem::exists(file, error_code))
            {
                if (error_code.value())
                {
                    throw exceptions::FileSystemError(
                        std::format(
                            "Failed to check if file exists for file: {}, error code {}",
                            file.string(),
                            error_code.value()
                        )
                    );
                }

                return {};
            }

            auto time = std::filesystem::last_write_time(file, error_code);
            if(error_code.value())
            {
                throw exceptions::FileSystemError(
                    std::format(
                        "Failed to get last write time for file: {}, error code {}",
                        file.string(),
                        error_code.value()
                    )
                );
            }

            return time;
        }

        TranslationUnit(SourceFile&& source, Configuration configuration)
            : _source(source)
            , _configuration(std::move(configuration))
        {
        }

        [[nodiscard]] const SourceFile& getSourceFile() const { return _source; }

        [[nodiscard]] const Configuration& getConfiguration() const { return _configuration; }

        [[nodiscard]] const std::filesystem::path& getObjectFile() const { return _objectFile; }

        [[nodiscard]] const std::filesystem::path& getDependencyFile() const { return _dependencyFile; }

        std::filesystem::file_time_type getLastWriteTimeBuild() const
        {
            const auto obj_time = getLastWriteTime(_objectFile);
            const auto dep_time = getLastWriteTime(_dependencyFile);

            return std::max(obj_time, dep_time);
        }

        void setObjectFile(const std::filesystem::path& path)
        {
            _objectFile = path;
            _last_write_time_build = getLastWriteTimeBuild();
        }

        void setDependencyFile(const std::filesystem::path& path)
        {
            _dependencyFile = path;
            _last_write_time_build = getLastWriteTimeBuild();
        }

        [[nodiscard]] bool isUpToDate() const
        {
            return !_objectFile.empty()
                && !_dependencyFile.empty()
                && _last_write_time_build != std::filesystem::file_time_type{}
                && _last_write_time_build > getLastWriteTime(_source.path());
        }

        void updateLastBuiltTime()
        {
            _last_write_time_build = getLastWriteTimeBuild();
        }
    };
}
