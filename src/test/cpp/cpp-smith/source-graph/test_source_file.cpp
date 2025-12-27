#include "test/Test.hpp"

#include "build/Project.hpp"
#include "build/source-graph/SourceFile.hpp"
#include "build/source-graph/SourceGraph.hpp"

namespace test
{
	using namespace cpp_smith;
	using namespace test;

	const auto cpp_smith_source_directory = std::filesystem::path(CPP_SMITH_SOURCE_DIR);

	struct Tests
	{
		Tests() = delete;

		static void testSourcefileFrom()
		{
			std::filesystem::path testPath = cpp_smith_source_directory/ "src/test/data/nested/test.hpp";
			testPath = std::filesystem::canonical(testPath);

			const GccProbe gcc_probe{};
			const SourceFile sourceFile = SourceFile::from(testPath, &gcc_probe);

			Assert::isFalse(sourceFile.directDependencies().empty());
			Assert::isFalse(sourceFile.systemDependencies().empty());
		}

		inline const static Test<void> test_sourcefile_from {
			"SourceFile gets dependencies", testSourcefileFrom
		};
	};
}
