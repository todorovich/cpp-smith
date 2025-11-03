#include "BuildSystem.hpp"
#include "artifacts/Executable.hpp"

#include "cpp-smith/source-graph/SourceFile.hpp"
#include "source-graph/SourceGraph.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cmake_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("SourceGraph gets dependencies", "[sourcefile]")
{
    BuildSystem buildSystem;

    const auto configuration = buildSystem.configuration("default").build();

    fs::path entryPoint = cmake_source_directory/ "src/test/data/main.cpp";

    const auto artifact = buildSystem
        .artifact<Executable>("executable")
        .entryPoint(entryPoint)
        .build();

    Executable* executable = artifact.get();
    SourceGraph sourceGraph = SourceGraph(executable, configuration);
}
