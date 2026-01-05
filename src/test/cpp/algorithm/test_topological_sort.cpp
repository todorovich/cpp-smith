#include <array>
#include <cstddef>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "algorithm/algorithm/TopologicalSort.hpp"
#include "test/Assert.hpp"
#include "test/Test.hpp"

namespace test
{
    struct Tests
    {
        Tests() = delete;

        class Node
        {
            std::string _key;
            std::vector<std::string> _deps;

        public:
            explicit Node(std::string key)
                : _key(std::move(key))
            {}

            [[nodiscard]] const std::string& key() const noexcept { return _key; }

            Node& dependsOn(std::string dep)
            {
                _deps.push_back(std::move(dep));
                return *this;
            }

            [[nodiscard]] std::span<const std::string> dependencies() const noexcept
            {
                return std::span<const std::string>(_deps.data(), _deps.size());
            }
        };

        [[nodiscard]] static const std::string& keyFrom(const Node* node) noexcept
        {
            return node->key();
        }

        [[nodiscard]] static std::span<const std::string> dependenciesFrom(const Node* node) noexcept
        {
            return node->dependencies();
        }


        static void kahn_sorts_nodes_from_span_of_nodes()
        {
            std::array nodes{ Node{"A"}, Node{"B"}, Node{"C"}, Node{"D"} };

            nodes[0].dependsOn("B").dependsOn("C");
            nodes[1].dependsOn("D");
            nodes[2].dependsOn("D");

            std::array order{ &nodes[0], &nodes[1], &nodes[2], &nodes[3] };

            cpp_smith::algorithm::DependencyGraph<Node, std::string> graph(
                std::span<Node*>{ order },
                &Tests::keyFrom,
                &Tests::dependenciesFrom
            );
            const cpp_smith::algorithm::KahnsTopologicalSorter sorter(graph);
            auto sorted = sorter.sorted();

            Assert::areEqual(4, sorted.size());
            Assert::areEqual(std::string{"D"}, sorted[0]->key());
            Assert::areEqual(std::string{"B"}, sorted[1]->key());
            Assert::areEqual(std::string{"C"}, sorted[2]->key());
            Assert::areEqual(std::string{"A"}, sorted[3]->key());
        }

        inline static const Test<void> topological_sort_with_kahns_algorithm{
            "kahn_toposort(span<Node*>, key_of, deps_of) orders nodes",
            kahn_sorts_nodes_from_span_of_nodes
        };
    };
}