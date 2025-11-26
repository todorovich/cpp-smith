#include "cpp-smith/artifacts/Executable.hpp"
#include "cpp-smith/Project.hpp"
#include "cpp-smith/source-graph/SourceGraph.hpp"

#include "cpp-prover/Test.hpp"

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

static prover::Test<void> test(
    "SourceGraph gets dependencies",
    []()->void {
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
);
