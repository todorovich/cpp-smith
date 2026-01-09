#include "test/Test.hpp"

#include "build/Project.hpp"
#include "compile/model/factory/ExecutableFactory.hpp"
#include "compile/model/factory/CompilationConfigurationFactory.hpp"
#include "system/System.hpp"

namespace test
{
	using namespace cpp_smith;
	using namespace test;

	struct Tests
	{
		Tests() = delete;

	    inline static logging::Logger logger = logging::Logger::defaultLogger("test::Tests");

		inline static const auto cpp_smith_source_directory = std::filesystem::path(CPP_SMITH_SOURCE_DIR);

        static void compileAndRunHelloWorld(const std::string& name, const std::filesystem::path& entryPoint)
        {
            std::filesystem::current_path(cpp_smith_source_directory);

            logger.print("CPP_SMITH_SOURCE_DIR: {}", CPP_SMITH_SOURCE_DIR);

            Project project {
                ProjectCoordinates {
                    "net.todorovich.test",
                    "test",
                    { 1, 2, 3 }
                }
            };

            project.withRootDirectory(cpp_smith_source_directory)
                .define<CompilationConfiguration>("standard")
                .withCompiler(CompilerType::GCC)
                .withPlatform(Platform::LINUX)
                .submit();

            project.define<Executable>(name)
                .addSource(entryPoint)
                .submit();

            project.build();

            const auto& configuration = project.getConfiguration<CompilationConfiguration>("standard");
            const std::filesystem::path executable_path =  configuration.projectDirectory()
                / configuration.buildDirectory()
                / name
                / configuration.name()
                / configuration.binaryDirectory() / std::string { name + ".exe" };

            Assert::isTrue(std::filesystem::exists(executable_path));

            const auto [exit_code, output] = System::ExecuteCommand(
                '"'+ executable_path.string() + '"' + " 2>&1"
            );

            Assert::areEqual(std::string("Hello, world!\n"), output);
        }

        inline const static Test<void, std::string, std::filesystem::path> compile_and_run_hello_world {
            "compileAndRunHelloWorld", compileAndRunHelloWorld,
            {
                { "hello world", cpp_smith_source_directory / "src/test/data/hello-world/hello_world.cpp" },
                { "hello relative", "src/test/data/hello-world/hello_world.cpp" }
            }
        };
	};
}
