#include "SourceGraph.hpp"

#include "../Exceptions.hpp"

#include <fstream>
#include <stack>
#include <stdexcept>

namespace cpp_smith {

    SourceGraph::SourceGraph(std::vector<std::filesystem::path> systemIncludePaths)
        : _systemIncludePaths(std::move(systemIncludePaths)) {}

    void SourceGraph::insert(const std::filesystem::path& root) {
        std::unordered_set<std::filesystem::path> visiting;
        std::unordered_set<std::filesystem::path> visited;
        _insertRecursive(root, visiting, visited);
    }

    const std::vector<const SourceFile*>& SourceGraph::ordered() const {
        return _buildOrder;
    }

    const SourceFile* SourceGraph::get(const std::filesystem::path& path) const {
        auto it = _filesByPath.find(path);
        return it != _filesByPath.end() ? it->second.get() : nullptr;
    }

    void SourceGraph::_insertRecursive(
        const std::filesystem::path& path,
        std::unordered_set<std::filesystem::path>& visiting,
        std::unordered_set<std::filesystem::path>& visited
    )
    {
        auto canonical_path = std::filesystem::canonical(path);

        if (visited.contains(canonical_path)) return;
        if (!visiting.insert(canonical_path).second)
        {
            throw IncludeCycleError("Include cycle detected at: " + canonical_path.string());
        }

        auto file = std::make_unique<SourceFile>(canonical_path);
        const auto& includes = file->includes();

        for (const auto& include : includes)
        {
            bool is_angled = include.starts_with('<');
            std::string include_name = include.substr(1, include.size() - 2);

            auto resolved = _resolveInclude(canonical_path, include_name, is_angled);
            if (!resolved.has_value())
            {
                throw UnresolvedIncludeError(
                    "Failed to resolve include: " + include +
                    " included by: " + canonical_path.string()
                );
            }

            // Only recurse into user headers
            if (!is_angled)
            {
                _insertRecursive(resolved.value(), visiting, visited);
            }
        }

        _buildOrder.push_back(file.get());
        _filesByPath[canonical_path] = std::move(file);
        visiting.erase(canonical_path);
        visited.insert(canonical_path);
    }


    std::optional<std::filesystem::path> SourceGraph::_resolveInclude(
        const std::filesystem::path& includingFile,
        const std::string& include,
        bool isAngled
    )
    {
        auto it = _includeCache.find(include);
        if (it != _includeCache.end()) return it->second;

        std::filesystem::path result;
        std::error_code ec;

        if (!isAngled)
        {
            if (auto localPath = includingFile.parent_path() / include;
                std::filesystem::exists(localPath, ec)
            )
            {
                result = std::filesystem::canonical(localPath, ec);
                return _includeCache[include] = result;
            }
        }

        for (const auto& dir : _systemIncludePaths)
        {
            if (auto tryPath = dir / include;
                std::filesystem::exists(tryPath, ec)
            )
            {
                result = std::filesystem::canonical(tryPath, ec);
                return _includeCache[include] = result;
            }
        }

        return _includeCache[include] = std::nullopt;
    }

} // namespace cpp_smith
