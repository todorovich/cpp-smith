#include "cpp-smith/Project.hpp"
#include "cpp-smith/artifacts/SharedLibrary.hpp"
#include "cpp-smith/artifacts/StaticLibrary.hpp"
#include "cpp-smith/configuration/Configuration.hpp"
#include "cpp-smith/configuration/ConfigurationBuilder.hpp"

#include "cpp-prover/Test.hpp"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

using namespace prover;

[[maybe_unused]] const static Test<void> test_configuration(
    "ConfigurationBuilder builds and Inspect",
    []
    {
        cpp_smith::Project build_system;
        build_system.define<cpp_smith::Configuration>("debug")
            .withCompiler(cpp_smith::CompilerType::GCC)
            .withPlatform("linux")
            .withArchitecture("x64")
            .addFlag("-g")
            .addDefine("DEBUG")
            .submit();

        const auto& config = build_system.getConfiguration("debug");
        Assert::areEqual(config.name(), std::string{"debug"});
        Assert::areEqual(config.platform(), std::string{"linux"});
        Assert::areEqual(config.architecture(), std::string{"x64"});
        Assert::areEqual(
            std::to_underlying(config.compiler()),
            std::to_underlying(cpp_smith::CompilerType::GCC)
        );
        Assert::areEqual(config.flags().size(), 1);
        Assert::areEqual(config.flags()[0], std::string{"-g"});

        Assert::areEqual(config.defines().size(), 1);
        Assert::areEqual(config.defines()[0], std::string{"DEBUG"});
    }
);

[[maybe_unused]] const static Test<void> test_configuration_builder(
    "ConfigurationBuilder builds and Inspect",
    []
    {
        cpp_smith::Project build_system;
        build_system.define<cpp_smith::Configuration>("debug")
            .withCompiler(cpp_smith::CompilerType::GCC)
            .withPlatform("linux")
            .withArchitecture("x64")
            .addFlag("-g")
            .addDefine("DEBUG")
            .submit();

        const auto& config = build_system.getConfiguration("debug");
        Assert::areEqual(config.name(), std::string{"debug"});
        Assert::areEqual(config.platform(), std::string{"linux"});
        Assert::areEqual(config.architecture(), std::string{"x64"});
        Assert::areEqual(
            std::to_underlying(config.compiler()),
            std::to_underlying(cpp_smith::CompilerType::GCC)
            );
        Assert::areEqual(config.flags().size(), 1);
        Assert::areEqual(config.flags()[0], std::string{"-g"});

        Assert::areEqual(config.defines().size(), 1);
        Assert::areEqual(config.defines()[0], std::string{"DEBUG"});
    }
);

[[maybe_unused]] const static Test<void> test_configuration_add_retrieve(
    "BuildSystem add and retrieve Configuration",
    []
    {
        cpp_smith::Configuration config(
            "release",
            cpp_smith::CompilerType::CLANG,
            "macos",
            "arm64",
            std::vector<std::string>{ "-O2" },
            std::vector<std::string>{ "NDEBUG" },
            std::vector<std::filesystem::path>{ "include/" },
            std::vector<std::filesystem::path>{ "/usr/include/" }
        );

        cpp_smith::Project build_system;
        build_system.accept(std::move(config));

        const auto& retrieved = build_system.getConfiguration("release");
        Assert::areEqual(retrieved.name(), std::string{"release"});

        Assert::areEqual(retrieved.flags().size(), 1);
        Assert::areEqual(retrieved.flags()[0], std::string{"-O2"});

        Assert::areEqual(retrieved.defines().size(), 1);
        Assert::areEqual(retrieved.defines()[0], std::string{"NDEBUG"});
    }
);

[[maybe_unused]] const static Test<void> test_static_library_build(
    "ArtifactBuilder<StaticLibrary> build and register",
    []
    {
        cpp_smith::Project build_system;
        build_system
            .define<cpp_smith::Configuration>("debug")
            .withPlatform("linux")
            .addFlag("-g")
            .submit();

        build_system
            .define<cpp_smith::StaticLibrary>("core")
            .addSource("src/core/math.cpp")
            .addSource("src/core/io.cpp")
            .submit();

        const auto& lib = build_system.getArtifact("core");
        Assert::areEqual(lib.name(), std::string{"core"});

        const auto& files = lib.sources();
        Assert::areEqual(files.size(), 2);
        Assert::areEqual(files[0].string(), std::string{"src/core/math.cpp"});
        Assert::areEqual(files[1].string(), std::string{"src/core/io.cpp"});
    }
);

[[maybe_unused]] const static Test<void> test_shared_library_build(
    "ArtifactBuilder<SharedLibrary> build and register",
    []
    {
        cpp_smith::Project build_system;
        build_system
            .define<cpp_smith::Configuration>("release")
            .withPlatform("macos")
            .withArchitecture("arm64")
            .addFlag("-O2")
            .submit();

        build_system
            .define<cpp_smith::SharedLibrary>("plugin")
            .addSource("src/plugin/entry.cpp")
            .addSource("src/plugin/helper.cpp")
            .submit();

        const auto& lib = build_system.getArtifact("plugin");
        Assert::areEqual(lib.name(), std::string{"plugin"});

        const auto& files = lib.sources();
        Assert::areEqual(files.size(), 2);
        Assert::areEqual(files[0].string(), std::string{"src/plugin/entry.cpp"});
        Assert::areEqual(files[1].string(), std::string{"src/plugin/helper.cpp"});
    }
);
