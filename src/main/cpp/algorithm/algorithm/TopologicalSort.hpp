#pragma once

#include <cstddef>
#include <functional>
#include <queue>
#include <span>
#include <vector>
#include <string>
#include <format>

#include "faults/faults.hpp"
#include "algorithm/DependencyGraph.hpp"

namespace cpp_smith::algorithm
{
    template <typename Node, DependencyGraphKeyType Key>
    class KahnsTopologicalSorter final
    {
        [[nodiscard]] static std::queue<std::size_t> init_zero_indegree_queue(const std::vector<int>& indegree)
        {
            std::queue<std::size_t> q;
            for (std::size_t i = 0; i < indegree.size(); ++i)
            {
                if (indegree[i] == 0)
                {
                    q.push(i);
                }
            }
            return q;
        }

        static void throw_cycle_fault(const std::vector<std::size_t>& cycle_indices)
        {
            throw faults::invalid::CircularDependency{
                std::format(
                    "kahn_toposort: circular dependency detected (cycle_nodes={})",
                    cycle_indices.size()
                ),
                cycle_indices
            };
        }

        std::vector<std::size_t> _order_indices;

        const DependencyGraph<Node, Key>& _graph;

    public:
        explicit KahnsTopologicalSorter(const DependencyGraph<Node, Key>& graph)
            : _graph(graph)
        {
            const std::size_t graph_size = graph.size();

            _order_indices.clear();
            _order_indices.reserve(graph_size);

            const auto& outgoing = graph.outgoing();

            auto indegree = graph.indegree();
            auto zero_indegree_queue = init_zero_indegree_queue(indegree);

            while (!zero_indegree_queue.empty())
            {
                const std::size_t u = zero_indegree_queue.front();
                zero_indegree_queue.pop();

                _order_indices.push_back(u);

                for (const std::size_t v : outgoing[u])
                {
                    --indegree[v];
                    if (indegree[v] == 0)
                    {
                        zero_indegree_queue.push(v);
                    }
                }
            }

            if (_order_indices.size() != graph_size)
            {
                std::vector<std::size_t> cycle_indices;
                cycle_indices.reserve(graph_size - _order_indices.size());

                for (std::size_t i = 0; i < graph_size; ++i)
                {
                    if (indegree[i] > 0)
                    {
                        cycle_indices.push_back(i);
                    }
                }

                throw_cycle_fault(cycle_indices);
            }
        }

        [[nodiscard]] std::vector<Node*> sorted() const
        {
            auto nodes = _graph.nodes();

            std::vector<Node*> ordered;
            ordered.reserve(_order_indices.size());

            for (const auto idx : _order_indices)
            {
                ordered.push_back(nodes[idx]);
            }

            return ordered;
        }
    };
}
