#include <catch2/catch_test_macros.hpp>

#include "cpp-smith/build/Configuration.hpp"
#include "cpp-smith/build/ConfigurationBuilder.hpp"
#include "cpp-smith/build/BuildSystem.hpp"

#include "cpp-smith/build/artifacts/ArtifactBuilder.hpp"
#include "cpp-smith/build/artifacts/Executable.hpp"
#include "cpp-smith/build/artifacts/StaticLibrary.hpp"
#include "cpp-smith/build/artifacts/SharedLibrary.hpp"

#include <filesystem>
#include <string>
#include <vector>

TEST_CASE("ConfigurationBuilder builds and Inspect", "[configuration]")
{
    cpp_smith::BuildSystem build_system;
    build_system.configuration("debug")
        .setCompiler("g++")
        .setPlatform("linux")
        .setArchitecture("x64")
        .addFlag("-g")
        .addDefine("DEBUG")
        .buildSystem();

    const auto& config = build_system.getConfiguration("debug");

    REQUIRE(config.name() == "debug");
    REQUIRE(config.platform() == "linux");
    REQUIRE(config.architecture() == "x64");
    REQUIRE(config.compiler().string() == "g++");

    REQUIRE(config.flags().size() == 1);
    CHECK(config.flags()[0] == "-g");

    REQUIRE(config.defines().size() == 1);
    CHECK(config.defines()[0] == "DEBUG");
}

TEST_CASE("BuildSystem add and retrieve Configuration", "[buildsystem]")
{
    cpp_smith::Configuration config(
        "release",
        "/usr/bin/clang++",
        std::vector<std::string>{ "-O2" },
        std::vector<std::string>{ "NDEBUG" },
        std::vector<std::filesystem::path>{ "include/" },
        std::vector<std::filesystem::path>{ "/usr/include/" },
        "macos",
        "arm64"
    );

    cpp_smith::BuildSystem build_system;
    build_system.add(std::move(config));

    const auto& retrieved = build_system.getConfiguration("release");
    REQUIRE(retrieved.name() == "release");

    REQUIRE(retrieved.flags().size() == 1);
    CHECK(retrieved.flags()[0] == "-O2");

    REQUIRE(retrieved.defines().size() == 1);
    CHECK(retrieved.defines()[0] == "NDEBUG");
}

TEST_CASE("ArtifactBuilder<Executable> build and register", "[artifact][executable]")
{
    cpp_smith::BuildSystem build_system;
    build_system
        .configuration("debug")
        .setPlatform("linux")
        .addFlag("-g")
        .buildSystem();

    build_system
        .artifact<cpp_smith::Executable>("app")
        .entryPoint("src/main.cpp")
        .buildSystem();

    const auto& artifact = build_system.getArtifact("app");
    REQUIRE(artifact.name() == "app");

    auto files = artifact.sourceFiles();
    REQUIRE(files.size() == 1);
    CHECK(files[0].string() == "src/main.cpp");
}

TEST_CASE("ArtifactBuilder<StaticLibrary> build and register", "[artifact][static]")
{
    cpp_smith::BuildSystem build_system;
    build_system
        .configuration("debug")
        .setPlatform("linux")
        .addFlag("-g")
        .buildSystem();

    // TODO: adding sources should

    build_system
        .artifact<cpp_smith::StaticLibrary>("core")
        .addSource("src/core/math.cpp")
        .addSource("src/core/io.cpp")
        .buildSystem();

    const auto& lib = build_system.getArtifact("core");
    REQUIRE(lib.name() == "core");

    auto files = lib.sourceFiles();
    REQUIRE(files.size() == 2);
    CHECK(files[0].string() == "src/core/math.cpp");
    CHECK(files[1].string() == "src/core/io.cpp");
}

TEST_CASE("ArtifactBuilder<SharedLibrary> build and register", "[artifact][shared]")
{
    cpp_smith::BuildSystem build_system;
    build_system
        .configuration("release")
        .setPlatform("macos")
        .setArchitecture("arm64")
        .addFlag("-O2")
        .buildSystem();

    build_system
        .artifact<cpp_smith::SharedLibrary>("plugin")
        .addSource("src/plugin/entry.cpp")
        .addSource("src/plugin/helper.cpp")
        .buildSystem();

    const auto& lib = build_system.getArtifact("plugin");
    REQUIRE(lib.name() == "plugin");

    auto files = lib.sourceFiles();
    REQUIRE(files.size() == 2);
    CHECK(files[0].string() == "src/plugin/entry.cpp");
    CHECK(files[1].string() == "src/plugin/helper.cpp");
}
