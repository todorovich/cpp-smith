#include "Project.hpp"
#include "Test.hpp"
#include "../../../../main/cpp/cpp-smith/artifacts/executable/Executable.hpp"
#include "source-graph/SourceFile.hpp"
#include "source-graph/SourceGraph.hpp"

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

[[maybe_unused]] const static prover::Test<void> test(
    "SourceFile gets dependencies",
    [] {
        fs::path testPath = cpp_smith_source_directory/ "src/test/data/nested/test.hpp";
        testPath = fs::canonical(testPath);

        const GccProbe gcc_probe{};
        const SourceFile sourceFile = SourceFile::from(testPath, &gcc_probe);

        prover::Assert::isFalse(sourceFile.directDependencies().empty());
        prover::Assert::isFalse(sourceFile.systemDependencies().empty());
    }
);
