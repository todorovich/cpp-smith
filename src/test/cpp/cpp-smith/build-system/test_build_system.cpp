#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#include "test/Test.hpp"

#include "build/Project.hpp"
#include "build/artifacts/SharedLibrary.hpp"
#include "build/artifacts/StaticLibrary.hpp"
#include "build/configuration/ConfigurationBuilder.hpp"
#include "compile/model/Configuration.hpp"

namespace test
{
    using namespace test;
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        static void testConfigurationBuilder()
        {
            Project project {
                ProjectCoordinates {
                    "net.todorovich.test",
                    "test",
                    { 1, 2, 3 }
                }
            };

            project.define<Configuration>("debug")
                .withCompiler(CompilerType::GCC)
                .withPlatform(Platform::LINUX)
                .withArchitecture(Architecture::X64)
                .addFlag("-g")
                .addDefine("DEBUG")
                .submit();

            const auto& config = project.getConfiguration("debug");
            Assert::areEqual(config.name(), std::string{"debug"});
            Assert::areEqual(config.platform(), Platform::LINUX);
            Assert::areEqual(config.architecture(), Architecture::X64);
            Assert::areEqual(
                std::to_underlying(config.compiler()),
                std::to_underlying(CompilerType::GCC)
            );
            Assert::areEqual(config.flags().size(), 1);
            Assert::areEqual(config.flags()[0], std::string{"-g"});

            Assert::areEqual(config.defines().size(), 1);
            Assert::areEqual(config.defines()[0], std::string{"DEBUG"});
        }

        inline const static Test<void> test_configuration_builder {
            "ConfigurationBuilder builds and Inspect", testConfigurationBuilder
        };

        static void testConfigurationAndRetrieve()
        {
            std::filesystem::path path = std::filesystem::current_path();

            Configuration config(
                    "release",
                    { CompilerType::CLANG, Platform::MAC_OS, Architecture::ARM_64 },
                    {path,path ,path ,path},
                    std::vector<std::string>{ "-O2" },
                    std::vector<std::string>{ "NDEBUG" },
                    std::vector<std::filesystem::path>{ "include/" },
                    std::vector<std::filesystem::path>{ "/usr/include/" }
                );

            Project build_system {
                ProjectCoordinates {
                    "net.todorovich",
                    "test configuration and retrieve",
                    { 1, 0, 0 }
                }
            };

            build_system.accept(std::move(config));

            const auto& retrieved = build_system.getConfiguration("release");
            Assert::areEqual(retrieved.name(), std::string{"release"});

            Assert::areEqual(retrieved.flags().size(), 1);
            Assert::areEqual(retrieved.flags()[0], std::string{"-O2"});

            Assert::areEqual(retrieved.defines().size(), 1);
            Assert::areEqual(retrieved.defines()[0], std::string{"NDEBUG"});
        }

        inline const static Test<void> test_configuration_add_retrieve {
            "BuildSystem add and retrieve Configuration", testConfigurationAndRetrieve
        };

        static void testStaticLibraryBuild()
        {
            Project project  {
                ProjectCoordinates {
                    "net.todorovich",
                    "test static library build",
                    { 1, 0, 0 }
                }
            };

            project
                .define<Configuration>("debug")
                .withPlatform(Platform::LINUX)
                .addFlag("-g")
                .submit();

            const auto core = project
                .define<StaticLibrary>("core")
                .addSource("src/core/math.cpp")
                .addSource("src/core/io.cpp")
                .submit();

            Assert::areEqual(std::string{"core"}, core->getCoordinates().artifact_name);

            const auto& files = core->sources();
            Assert::areEqual(files.size(), 2);
            Assert::areEqual(files[0].string(), std::string{"src/core/math.cpp"});
            Assert::areEqual(files[1].string(), std::string{"src/core/io.cpp"});
        }

        inline const static Test<void> test_static_library_build {
            "ArtifactBuilder<StaticLibrary> build and register", testStaticLibraryBuild
        };

        static void testSharedLibraryBuild()
        {
            Project project  {
                ProjectCoordinates {
                    "net.todorovich",
                    "test shared library builder",
                    { 1, 0, 0 }
                }
            };

            project
                .define<Configuration>("release")
                .withPlatform(Platform::MAC_OS)
                .withArchitecture(Architecture::ARM_64)
                .addFlag("-O2")
                .submit();

            const auto plugin = project
                .define<SharedLibrary>("plugin")
                .addSource("src/plugin/entry.cpp")
                .addSource("src/plugin/helper.cpp")
                .submit();

            const auto& lib = project.getArtifact("plugin");
            Assert::areEqual(std::string{"plugin"}, lib.getCoordinates().artifact_name);

            const auto& files = plugin->sources();
            Assert::areEqual(files.size(), 2);
            Assert::areEqual(files[0].string(), std::string{"src/plugin/entry.cpp"});
            Assert::areEqual(files[1].string(), std::string{"src/plugin/helper.cpp"});
        }

        inline const static Test<void> test_shared_library_build {
            "ArtifactBuilder<SharedLibrary> build and register", testSharedLibraryBuild
        };
    };
}