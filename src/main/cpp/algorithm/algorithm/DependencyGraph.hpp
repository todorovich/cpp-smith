#pragma once

#include <concepts>
#include <cstddef>
#include <format>
#include <functional>
#include <span>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "faults/faults.hpp"

namespace cpp_smith::algorithm
{
    template <typename T>
    concept DependencyGraphKeyType = std::copy_constructible<T>
        && std::equality_comparable<T>
        && requires(const T& t)
        {
            { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
        };

    template <typename Node, DependencyGraphKeyType Key>
    class DependencyGraph final
    {
        std::span<Node*> _nodes;
        std::vector<std::pair<Key, Key>> _missing_dependencies;
        std::vector<int> _indegree;
        std::vector<std::vector<std::size_t>> _outgoing;

        static constexpr bool _key_formattable = requires(const Key& k) { std::format("{}", k); };

        [[nodiscard]] static std::string format_missing_dependencies_details(
            const std::vector<std::pair<Key, Key>>& missing
        )
        {
            if constexpr (!_key_formattable)
            {
                return {};
            }
            else
            {
                std::string out;
                for (std::size_t i = 0; i < missing.size(); ++i)
                {
                    const auto& [node_key, dep_key] = missing[i];
                    out += std::format("({} <- {})", node_key, dep_key);
                    if (i + 1 < missing.size())
                    {
                        out += ", ";
                    }
                }
                return out;
            }
        }

        void throw_if_missing() const
        {
            if (_missing_dependencies.empty())
            {
                return;
            }

            throw faults::missing::Dependency{
                std::format(
                    "kahn_toposort: missing dependencies (count={})",
                    _missing_dependencies.size()
                ),
                _missing_dependencies.size(),
                format_missing_dependencies_details(_missing_dependencies)
            };
        }

    public:
        template <class KeyOf, class DepsOf>
            requires std::regular_invocable<KeyOf, Node*> &&
                     std::convertible_to<std::invoke_result_t<KeyOf, Node*>, Key> &&
                     std::regular_invocable<DepsOf, Node*> &&
                     (
                         std::same_as<
                             std::remove_cvref_t<std::invoke_result_t<DepsOf, Node*>>,
                             std::span<const Key>
                         >
                         ||
                         std::same_as<
                             std::remove_cvref_t<std::invoke_result_t<DepsOf, Node*>>,
                             std::span<Node* const>
                         >
                         ||
                         std::same_as<
                             std::remove_cvref_t<std::invoke_result_t<DepsOf, Node*>>,
                             std::span<const Node* const>
                         >
                     )
        explicit DependencyGraph(
            std::span<Node*> nodes,
            KeyOf key_of,
            DepsOf deps_of
        )
            : _nodes(nodes)
        {
            const std::size_t n = _nodes.size();

            std::vector<Key> keys;
            keys.reserve(n);

            std::unordered_map<Key, std::size_t> index_of;
            index_of.reserve(n);

            for (std::size_t i = 0; i < n; ++i)
            {
                if (_nodes[i] == nullptr)
                {
                    throw faults::invalid::Argument{ "DependencyGraph: nodes contains nullptr" };
                }

                Key k = static_cast<Key>(std::invoke(key_of, _nodes[i]));
                keys.push_back(k);
                index_of.emplace(keys.back(), i);
            }

            _indegree.assign(n, 0);
            _outgoing.resize(n);

            for (std::size_t i = 0; i < n; ++i)
            {
                const Key node_key = keys[i];

                using DepsResult = std::remove_cvref_t<std::invoke_result_t<DepsOf, Node*>>;
                const DepsResult deps = std::invoke(deps_of, _nodes[i]);

                if constexpr (std::same_as<DepsResult, std::span<const Key>>)
                {
                    for (const Key& dep_key : deps)
                    {
                        const auto it = index_of.find(dep_key);
                        if (it == index_of.end())
                        {
                            _missing_dependencies.emplace_back(node_key, dep_key);
                            continue;
                        }

                        const std::size_t dep_idx = it->second;
                        _outgoing[dep_idx].push_back(i); // dep -> node
                        ++_indegree[i];
                    }
                }
                else
                {
                    for (const auto dep_ptr : deps)
                    {
                        if (dep_ptr == nullptr)
                        {
                            throw faults::invalid::Argument{ "DependencyGraph: dependencies contains nullptr" };
                        }

                        const Key dep_key = static_cast<Key>(std::invoke(key_of, const_cast<Node*>(dep_ptr)));

                        const auto it = index_of.find(dep_key);
                        if (it == index_of.end())
                        {
                            _missing_dependencies.emplace_back(node_key, dep_key);
                            continue;
                        }

                        const std::size_t dep_idx = it->second;
                        _outgoing[dep_idx].push_back(i); // dep -> node
                        ++_indegree[i];
                    }
                }
            }

            throw_if_missing();
        }

        [[nodiscard]] std::span<Node*> nodes() const noexcept { return _nodes; }
        [[nodiscard]] std::size_t size() const noexcept { return _nodes.size(); }

        [[nodiscard]] const std::vector<int>& indegree() const noexcept { return _indegree; }
        [[nodiscard]] const std::vector<std::vector<std::size_t>>& outgoing() const noexcept { return _outgoing; }
    };
}