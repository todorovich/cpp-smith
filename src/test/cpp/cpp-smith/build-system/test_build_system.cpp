#include <catch2/catch_test_macros.hpp>

#include "Project.hpp"
#include "artifacts/ArtifactBuilder.hpp"
#include "artifacts/Executable.hpp"
#include "artifacts/SharedLibrary.hpp"
#include "artifacts/StaticLibrary.hpp"
#include "configuration/Configuration.hpp"
#include "configuration/ConfigurationBuilder.hpp"

#include <filesystem>
#include <string>
#include <vector>

TEST_CASE("ConfigurationBuilder builds and Inspect", "[configuration]")
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

    REQUIRE(config.name() == "debug");
    REQUIRE(config.platform() == "linux");
    REQUIRE(config.architecture() == "x64");
    REQUIRE(config.compiler() == cpp_smith::CompilerType::GCC);

    REQUIRE(config.flags().size() == 1);
    CHECK(config.flags()[0] == "-g");

    REQUIRE(config.defines().size() == 1);
    CHECK(config.defines()[0] == "DEBUG");
}

TEST_CASE("BuildSystem add and retrieve Configuration", "[buildsystem]")
{
    cpp_smith::Configuration config(
        "release",
        cpp_smith::CompilerType::CLANG,
        std::vector<std::string>{ "-O2" },
        std::vector<std::string>{ "NDEBUG" },
        std::vector<std::filesystem::path>{ "include/" },
        std::vector<std::filesystem::path>{ "/usr/include/" },
        "macos",
        "arm64"
    );

    cpp_smith::Project build_system;
    build_system.accept(std::move(config));

    const auto& retrieved = build_system.getConfiguration("release");
    REQUIRE(retrieved.name() == "release");

    REQUIRE(retrieved.flags().size() == 1);
    CHECK(retrieved.flags()[0] == "-O2");

    REQUIRE(retrieved.defines().size() == 1);
    CHECK(retrieved.defines()[0] == "NDEBUG");
}



TEST_CASE("ArtifactBuilder<StaticLibrary> build and register", "[artifact][static]")
{
    cpp_smith::Project build_system;
    build_system
        .define<cpp_smith::Configuration>("debug")
        .withPlatform("linux")
        .addFlag("-g")
        .submit();

    // TODO: adding sources should

    build_system
        .define<cpp_smith::StaticLibrary>("core")
        .addSource("src/core/math.cpp")
        .addSource("src/core/io.cpp")
        .submit();

    const auto& lib = build_system.getArtifact("core");
    REQUIRE(lib.name() == "core");

    auto files = lib.sources();
    REQUIRE(files.size() == 2);
    CHECK(files[0].string() == "src/core/math.cpp");
    CHECK(files[1].string() == "src/core/io.cpp");
}

TEST_CASE("ArtifactBuilder<SharedLibrary> build and register", "[artifact][shared]")
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
    REQUIRE(lib.name() == "plugin");

    auto files = lib.sources();
    REQUIRE(files.size() == 2);
    CHECK(files[0].string() == "src/plugin/entry.cpp");
    CHECK(files[1].string() == "src/plugin/helper.cpp");
}
