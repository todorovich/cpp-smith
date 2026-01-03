#include <filesystem>
#include <string>

#include "test/Test.hpp"

#include "build/Project.hpp"
#include "compile/model/factory/StaticLibraryFactory.hpp"
#include "compile/model/factory/CompilationConfigurationFactory.hpp"

namespace test
{
    using namespace cpp_smith;
    using namespace test;

    struct Tests
    {
        Tests() = delete;

        inline static const auto cpp_smith_source_directory = std::filesystem::path(CPP_SMITH_SOURCE_DIR);

        static void testStaticLibraryBuilder()
        {
            Project project{
                ProjectCoordinates{
                    "net.todorovich.test",
                    "test",
                    { 1, 2, 3 }
                }
            };

            project.withRootDirectory(cpp_smith_source_directory)
                .define<CompilationConfiguration>("standard")
                .withCompiler(CompilerType::GCC)
                .withPlatform(Platform::LINUX)
                .withArchitecture(Architecture::X64)
                .submit();

            const auto lib = project.define<StaticLibrary>("hello_library")
                .addSource("src/test/data/hello-library/hello_library.cpp")
                .submit();

            Assert::areEqual(std::string("hello_library"), lib.getCoordinates().artifact_name);

            project.build();

            const auto& configuration = project.getConfiguration("standard")
                .as<CompilationConfiguration>();
            const std::filesystem::path archive_path =
                configuration.projectDirectory()
                / configuration.buildDirectory()
                / "hello_library"
                / configuration.name()
                / configuration.libraryDirectory()
                / "libhello_library.a";

            Assert::isTrue(
                std::filesystem::exists(archive_path),
                std::string("Expected static library output missing at: ") + archive_path.string()
            );
        }

        inline const static Test<void> test_static_library_builder{
            "ArtifactBuilder<StaticLibrary> build and register",
            testStaticLibraryBuilder
        };
    };
}