#include <catch2/catch_test_macros.hpp>
#include "cpp-smith/source-graph/SourceGraph.hpp"
#include "cpp-smith/Exceptions.hpp"

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceGraph detects include cycles", "[sourcegraph]")
{
    SourceGraph graph({});
    REQUIRE_THROWS_AS(
        graph.insert(cmake_source_directory / "src/test/data/cycle_a.hpp"),
        IncludeCycleError
    );
}
