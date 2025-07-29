#include <catch2/catch_test_macros.hpp>
#include "cpp-smith/source-graph/SourceGraph.hpp"

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

// TODO this doesnt prove this at all

TEST_CASE("SourceGraph resolves angled includes using system paths", "[sourcegraph]") {
    std::vector<fs::path> systemPaths = {
        "/usr/include", "/usr/include/c++/14", "/usr/lib/llvm-18/include"
    };

    SourceGraph graph(systemPaths);
    graph.insert(cmake_source_directory / "src/test/data/nested/test.hpp"); // test.hpp includes <vector>

    const auto& ordered = graph.ordered();
    REQUIRE_FALSE(ordered.empty());
    REQUIRE(ordered.back()->path().filename() == "test.hpp");
}