#include "test/Test.hpp"

#include "build/Project.hpp"
#include "build/builders/ExecutableBuilder.hpp"
#include "compile/model/Configuration.hpp"

namespace test
{
	using namespace cpp_smith;
	using namespace test;

	struct Tests
	{
		Tests() = delete;

		static void testExecutableBuilder()
		{
			Project build_system {
				ProjectCoordinates {
					"net.todorovich.test",
					"test",
					{ 1, 2, 3 }
				}
			};

			auto configuration = build_system.define<Configuration>("debug")
				.withCompiler(CompilerType::GCC)
				.withPlatform(Platform::LINUX)
				.withArchitecture(Architecture::X64)
				.addFlag("-g")
				.addDefine("DEBUG")
				.create();

			const auto executable = build_system.define<cpp_smith::Executable>("app")
				.addSource("src/main.cpp")
				.submit();

			Assert::areEqual(std::string("app"), executable->getCoordinates().artifact_name);

			const auto& files = executable->sources();
			Assert::areEqual(1, files.size());
			Assert::areEqual(std::string("src/main.cpp"), files[0].string());
		}

		inline const static Test<void> test_executable_builder {
			"ArtifactBuilder<Executable> build and register", testExecutableBuilder
		};
	};
}
