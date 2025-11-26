#include "cpp-smith/Project.hpp"
#include "cpp-smith/artifacts/Executable.hpp"
#include "cpp-smith/configuration/Configuration.hpp"
#include "cpp-smith/compiler-probe/GccProbe.hpp"
#include "cpp-prover/Test.hpp"

using namespace prover;

static Test<void> test(
    "ArtifactBuilder<Executable> build and register",
    []() -> void
    {
        cpp_smith::Project build_system;

        auto configuration = build_system.define<cpp_smith::Configuration>("debug")
            .withCompiler(cpp_smith::CompilerType::GCC)
            .withPlatform("linux")
            .withArchitecture("x64")
            .addFlag("-g")
            .addDefine("DEBUG")
            .create();

        const auto executable = build_system.define<cpp_smith::Executable>("app")
            .addSource("src/main.cpp")
            .create();

        Assert::areEqual(std::string("app"), executable->name());

        const auto files = executable->sources();
        Assert::areEqual(1, files.size());
        Assert::areEqual(std::string("src/main.cpp"), files[0].string());
    }
);
