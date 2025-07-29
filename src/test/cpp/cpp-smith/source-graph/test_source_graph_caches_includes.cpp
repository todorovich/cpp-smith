#include <catch2/catch_test_macros.hpp>
#include "cpp-smith/source-graph/SourceGraph.hpp"

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceGraph resolves quoted includes", "[sourcegraph]")
{
    fs::path testPath = cmake_source_directory/ "src/test/data/nested/test.hpp";
    testPath = fs::canonical(testPath);

    SourceGraph graph({});
    graph.insert(testPath);

    const auto& ordered = graph.ordered();
    REQUIRE(ordered.size() == 2);
    REQUIRE(ordered[0]->path().filename() == "a.hpp");
    REQUIRE(ordered[1]->path().filename() == "test.hpp");
}

