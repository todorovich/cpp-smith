#include "cpp-smith/BuildEnvironment.hpp"
#include "cpp-smith/compiler-probe/CompilerProbe.hpp"

#include <catch2/catch_test_macros.hpp>

#include <fstream>
#include <algorithm>

using namespace cpp_smith;

namespace {

    std::filesystem::path writeTestFile(const std::string& contents)
    {
        std::filesystem::path temp = std::filesystem::temp_directory_path() / "test_dep.cpp";
        std::ofstream out(temp);
        out << contents;
        return temp;
    }

} // namespace

TEST_CASE("BuildEnvironment resolves hello_world.cpp", "[BuildEnvironment]")
{
    ClangProbe probe;
    BuildEnvironment env(
        probe.findCompiler(),
        {},
        {},
        probe.getSystemIncludes()
    );

    const auto test_root = std::filesystem::path(TEST_DATA_DIR);
    const auto source = test_root / "hello_world.cpp";

    auto deps = env.resolveDependenciesFor(source);

    REQUIRE_FALSE(deps.empty());
    REQUIRE(std::find(deps.begin(), deps.end(), source) != deps.end());

    bool has_print = std::ranges::any_of(
        deps,
        [](const std::filesystem::path& p) { return p.filename() == "print"; }
    );

    REQUIRE(has_print);
}

