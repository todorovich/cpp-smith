#include "cpp-prover/Test.hpp"

#include "Project.hpp"
#include "cpp-smith/artifacts/Executable.hpp"
#include "compiler-probe/ProbeUtils.hpp"

#include <filesystem>
#include <print>

using namespace prover;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

[[maybe_unused]] const static Test<void, std::string> test(
    "Compile and Run hello_world.cpp",
    [](const std::string& name)
    {
        std::println("CPP_SMITH_SOURCE_DIR: {}", CPP_SMITH_SOURCE_DIR);

        // TODO: i should be able to pass in relative paths to the addSource command
        const std::filesystem::path entryPoint = cpp_smith_source_directory / "src/test/data/hello_world.cpp";

        cpp_smith::Project project;
        project.withRootDirectory(cpp_smith_source_directory)
            .define<cpp_smith::Configuration>("standard")
            .withCompiler(cpp_smith::CompilerType::GCC)
            .withPlatform("linux")
            .submit()
            .define<cpp_smith::Executable>(name)
            .addSource(entryPoint)
            .submit()
            .build();

        const fs::path executable = project.getInstallDirectory() / std::string { name + ".exe" };

        Assert::isTrue(fs::exists(executable));

        const std::string output = ExecuteCommandAndCaptureOutput('"'+ executable.string() + '"' + " 2>&1");

        Assert::areEqual(std::string("Hello, world!\n"), output);
    },
    {"hello world"}
);
