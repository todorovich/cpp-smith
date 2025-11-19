#include <catch2/catch_test_macros.hpp>

#include "../../../../main/cpp/cpp-smith/Project.hpp"
#include "cpp-smith/build/artifacts/Executable.hpp"
#include "cpp-smith/build/configuration/Configuration.hpp"
#include "cpp-smith/compiler-probe/GccProbe.hpp"

TEST_CASE("ArtifactBuilder<Executable> build and register", "[artifact][executable]")
{
    cpp_smith::Project build_system;

    auto configuration = build_system.define<cpp_smith::Configuration>("debug")
        .withCompiler(cpp_smith::CompilerType::GCC)
        .withPlatform("linux")
        .withArchitecture("x64")
        .addFlag("-g")
        .addDefine("DEBUG")
        .create();

    auto executable = build_system.define<cpp_smith::Executable>("app")
        .addSource("src/main.cpp")
        .create();

    REQUIRE(executable->name() == "app");

    auto files = executable->sources();
    REQUIRE(files.size() == 1);
    CHECK(files[0].string() == "src/main.cpp");
}
