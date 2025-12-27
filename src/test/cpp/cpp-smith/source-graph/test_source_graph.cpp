#include "test/Test.hpp"

#include "build/artifacts/Executable.hpp"
#include "build/Project.hpp"
#include "build/source-graph/SourceGraph.hpp"

namespace test
{
	using namespace cpp_smith;
	using namespace test;

	struct Tests
	{
		inline static const auto cpp_smith_source_directory = fs::path(CPP_SMITH_SOURCE_DIR);

		Tests() = delete;

		static void testSourceGraph()
		{
			Project buildSystem {
				ProjectCoordinates { "net.todorovich.test", "test", "test" }
			};

			const auto configuration = buildSystem.define<Configuration>("default").create();

			const std::filesystem::path entryPoint = cpp_smith_source_directory/ "src/test/data/main.cpp";

			const auto executable = buildSystem
				.define<Executable>("executable")
				.addSource(entryPoint)
				.submit();

			const auto sourceGraph = SourceGraph(executable, configuration);
		}

		inline const static Test<void> test {
			"SourceGraph gets dependencies", testSourceGraph
		};
	};
}

