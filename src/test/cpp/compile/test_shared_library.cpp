#include <filesystem>
#include <string>

#include "test/Test.hpp"

#include "build/Project.hpp"
#include "compile/model/factory/SharedLibraryFactory.hpp"
#include "compile/model/factory/CompilationConfigurationFactory.hpp"

namespace test
{
    using namespace cpp_smith;
    using namespace test;

    struct Tests
    {
        Tests() = delete;

        inline static const auto cpp_smith_source_directory = std::filesystem::path(CPP_SMITH_SOURCE_DIR);

        static void testSharedLibraryBuilder()
        {
            Project project{
                ProjectCoordinates{
                    "net.todorovich.test",
                    "test",
                    { 1, 2, 3 }
                }
            };

            const auto& configuration = project.withRootDirectory(cpp_smith_source_directory)
                .define<CompilationConfiguration>("standard")
                .withCompiler(CompilerType::GCC)
                .withPlatform(Platform::LINUX)
                .withArchitecture(Architecture::X64)
                .submit();

            const auto shared = project.define<SharedLibrary>("hello_library")
                .addSource("src/test/data/hello-library/hello_library.cpp")
                .submit();

            Assert::areEqual(std::string("hello_library"), shared.getCoordinates().artifact_name);

            project.build();

            const auto path = shared.getSharedLibraryFile(&configuration).getLinkable();
            Assert::isTrue(
                std::filesystem::exists(path),
                std::string("Expected shared library output missing at: ") + path.string()
            );
        }

        inline const static Test<void> test_shared_library_builder{
            "ArtifactBuilder<SharedLibrary> build and register",
            testSharedLibraryBuilder
        };
    };
}