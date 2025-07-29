
#include <catch2/catch_test_macros.hpp>
#include "cpp-smith/source-graph/SourceGraph.hpp"
#include <print>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceGraph caches resolved includes", "[sourcegraph]") {
    auto pwd = std::filesystem::current_path();
    std::println("CWD: {}", pwd.string());

    SourceGraph graph({});
    graph.insert(cmake_source_directory / "src/test/data/nested/test.hpp"); // includes "a.hpp"

    // Internal state: test indirect include resolution
    const auto* file = graph.get(cmake_source_directory / "src/test/data/a.hpp");
    REQUIRE(file != nullptr);

    // Re-insert shouldn't trigger re-parse
    graph.insert( cmake_source_directory / "src/test/data/nested/test.hpp");
    REQUIRE(graph.ordered().size() == 2);
}
