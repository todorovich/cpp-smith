#include "fault/faults.hpp"

#include "test/Test.hpp"

#include "build/Project.hpp"

namespace test
{
    using namespace test;

    struct Tests
    {
        Tests() = delete;

        static void testProject()
        {
            Assert::throwsException<faults::NotFound>(
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
