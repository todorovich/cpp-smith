#include "../../../../main/cpp/cpp-smith/Project.hpp"
#include "build/artifacts/Executable.hpp"

#include "source-graph/SourceFile.hpp"
#include "source-graph/SourceGraph.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceGraph gets dependencies", "[sourcefile]")
{
    Project buildSystem;

    const auto configuration = buildSystem.define<Configuration>("default").create();

    fs::path entryPoint = cpp_smith_source_directory/ "src/test/data/main.cpp";

    const auto artifact = buildSystem
        .define<Executable>("executable")
        .addSource(entryPoint)
        .create();

    Executable* executable = artifact.get();
    SourceGraph sourceGraph = SourceGraph(executable, configuration);
}
