#pragma once

#include "SourceFile.hpp"
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace cpp_smith {

    class SourceGraph {
    public:
        explicit SourceGraph(std::vector<std::filesystem::path> systemIncludePaths);

        void insert(const std::filesystem::path& root);
        const std::vector<const SourceFile*>& ordered() const;

        const SourceFile* get(const std::filesystem::path& path) const;

    private:
        std::vector<std::filesystem::path> _systemIncludePaths;

        // All known source files, keyed by canonical path
        std::unordered_map<std::filesystem::path, std::unique_ptr<SourceFile>> _filesByPath;

        // Cache for previously resolved includes
        std::unordered_map<std::string, std::optional<std::filesystem::path>> _includeCache;

        // Topologically ordered list after insertion
        std::vector<const SourceFile*> _buildOrder;

        void _insertRecursive(const std::filesystem::path& path,
                              std::unordered_set<std::filesystem::path>& visiting,
                              std::unordered_set<std::filesystem::path>& visited);

        std::optional<std::filesystem::path> _resolveInclude(
            const std::filesystem::path& includingFile,
            const std::string& include,
            bool isAngled);
    };

} // namespace cpp_smith
