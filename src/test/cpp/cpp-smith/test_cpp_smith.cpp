#include "cpp-prover/Test.hpp"

#include "Project.hpp"
#include "cpp-smith/artifacts/Executable.hpp"
#include "compiler-probe/ProbeUtils.hpp"

#include <filesystem>
#include <print>

using namespace prover;

const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

struct Tests
{
    static void compileAndRunHelloWorld(const std::string& name, const std::filesystem::path& entryPoint)
    {
        std::println("CPP_SMITH_SOURCE_DIR: {}", CPP_SMITH_SOURCE_DIR);

        cpp_smith::Project project;
        project.withRootDirectory(cpp_smith_source_directory)
            .define<cpp_smith::Configuration>("standard")
            .withCompiler(cpp_smith::CompilerType::GCC)
            .withPlatform(cpp_smith::Platform::LINUX)
            .submit();

        project.define<cpp_smith::Executable>(name)
            .addSource(entryPoint)
            .submit();

        project.build();

        const fs::path executable_path =  project.getConfiguration("standard")
            .binaryDirectory() / std::string { name + ".exe" };

        Assert::isTrue(fs::exists(executable_path));

        const auto [exit_code, output] = System::ExecuteCommand(
            '"'+ executable_path.string() + '"' + " 2>&1"
        );

        Assert::areEqual(std::string("Hello, world!\n"), output);
    }

    inline const static Test<void, std::string, std::filesystem::path> compile_and_run_hello_world {
        "compileAndRunHelloWorld", compileAndRunHelloWorld,
        {
            { "hello world", cpp_smith_source_directory / "src/test/data/hello_world.cpp" },
            { "hello relative", "src/test/data/hello_world.cpp" }
        }
    };
};
