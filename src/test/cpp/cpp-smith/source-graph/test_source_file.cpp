#include "Project.hpp"
#include "artifacts/Executable.hpp"
#include "source-graph/SourceFile.hpp"
#include "source-graph/SourceGraph.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceFile gets dependencies", "[sourcefile]")
{
    fs::path testPath = cpp_smith_source_directory/ "src/test/data/nested/test.hpp";
    testPath = fs::canonical(testPath);
    GccProbe gcc_probe{};

    const SourceFile sourceFile = SourceFile::from(testPath, &gcc_probe);

    REQUIRE(!sourceFile.directDependencies().empty());
    REQUIRE(!sourceFile.systemDependencies().empty());
}
