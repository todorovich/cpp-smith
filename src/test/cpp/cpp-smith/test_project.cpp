#include "exceptions/Exceptions.hpp"

#include "cpp-prover/Test.hpp"

#include "cpp-smith/Project.hpp"

namespace test
{
    using namespace prover;

    struct Tests
    {
        Tests() = delete;

        static void testProject()
        {
            Assert::throwsException<exceptions::NotFound>(
                []
                {
                    const cpp_smith::Project project {
                        cpp_smith::ProjectCoordinates { "net.todorovich.test", "test", "test" }
                    };
                    auto config = project.getConfiguration("doesn't exist");
                }
            );
        }

        inline static const Test<void> test_project {
            "Project::getConfiguration throws CppSmithException", testProject
        };
    };
}
