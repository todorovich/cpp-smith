#include <filesystem>
#include <print>

#include "test/Test.hpp"

#include "build/Project.hpp"
#include "build/artifacts/Executable.hpp"
#include "build/compiler-probe/ProbeUtils.hpp"

namespace test
{
    using namespace cpp_smith;
    using namespace test;

    struct Tests
    {
        Tests() = delete;

        inline static const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

        static void compileAndRunHelloWorld(const std::string& name, const std::filesystem::path& entryPoint)
        {
            std::println("CPP_SMITH_SOURCE_DIR: {}", CPP_SMITH_SOURCE_DIR);

            Project project {
                ProjectCoordinates { "net.todorovich.test", "test", "test" }
            };

            project.withRootDirectory(cpp_smith_source_directory)
                .define<Configuration>("standard")
                .withCompiler(CompilerType::GCC)
                .withPlatform(Platform::LINUX)
                .submit();

            project.define<Executable>(name)
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
}
