#include "BuildSystem.hpp"
#include "artifacts/Executable.hpp"

#include "cpp-smith/source-graph/SourceFile.hpp"
#include "source-graph/SourceGraph.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceFile gets dependencies", "[sourcefile]")
{
    fs::path testPath = cmake_source_directory/ "src/test/data/nested/test.hpp";
    testPath = fs::canonical(testPath);

    const SourceFile sourceFile = SourceFile::from(testPath);

    REQUIRE(!sourceFile.directDependencies().empty());
    REQUIRE(!sourceFile.systemDependencies().empty());
}
