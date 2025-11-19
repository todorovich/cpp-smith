#include "compiler-probe/ProbeUtils.hpp"
#include "cpp-smith/Project.hpp"
#include "cpp-smith/artifacts/Executable.hpp"

#include <catch2/catch_test_macros.hpp>
#include <print>

using namespace cpp_smith;
namespace fs = std::filesystem;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

TEST_CASE("Build Hello World", "[cpp-smith]")
{
    std::println("CPP_SMITH_SOURCE_DIR: {}", CPP_SMITH_SOURCE_DIR);

    // TODO: i should be able to pass in relative paths to the addSource command
    const fs::path entryPoint = cpp_smith_source_directory / "src/test/data/hello_world.cpp";

    Project project;
    project.withRootDirectory(cpp_smith_source_directory)
        .define<Configuration>("standard")
        .withCompiler(CompilerType::GCC)
        .withPlatform("linux")
        .submit()
        .define<Executable>("executable")
        .addSource(entryPoint)
        .submit()
        .build();

    const fs::path executable = project.getInstallDirectory() / "executable.exe";

    REQUIRE(fs::exists(executable));
    const std::string output = ExecuteCommandAndCaptureOutput(executable.string() + " 2>&1");
    REQUIRE(output == "Hello, world!\n");
}
