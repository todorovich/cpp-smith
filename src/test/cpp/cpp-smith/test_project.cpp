#include "cpp-prover/Test.hpp"
#include "cpp-smith/Project.hpp"
#include "exceptions/Exceptions.hpp"

using namespace prover;

[[maybe_unused]] const static Test<void> test(
    "Project::getConfiguration throws CppSmithException",
    []{
        Assert::throwsException<exceptions::NotFound>(
            []
            {
                const cpp_smith::Project project;
                auto config = project.getConfiguration("doesn't exist");
            }
        );
    }
);