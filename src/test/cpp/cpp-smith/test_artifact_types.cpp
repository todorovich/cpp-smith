#include "test/Test.hpp"

#include "build/artifacts/ArtifactTypes.hpp"
#include "build/artifacts/ArtifactType.hpp"

namespace test
{
    using namespace test;
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        static void testArtifactTypesEmptyByDefault()
        {
            const ArtifactTypes types;

            Assert::isTrue(types.empty(), "default-constructed ArtifactTypes should be empty");
            Assert::areEqual(std::size_t{0}, types.size(), "default-constructed ArtifactTypes should have size 0");
            Assert::isFalse(types.contains(ArtifactType::of<int>()), "empty ArtifactTypes should not contain any type");
        }

        inline const static Test<void> artifact_types_empty_by_default {
            "ArtifactTypes is empty by default", testArtifactTypesEmptyByDefault
        };

        static void testArtifactTypesInitializerListDedupAndContains()
        {
            const ArtifactType ti = ArtifactType::of<int>();
            const ArtifactType td = ArtifactType::of<double>();

            const ArtifactTypes types { ti, ti, td };

            Assert::isFalse(types.empty(), "initializer_list ArtifactTypes should not be empty when given elements");
            Assert::areEqual(std::size_t{2}, types.size(), "initializer_list should deduplicate identical ArtifactType values");
            Assert::isTrue(types.contains(ti), "contains(int) should be true");
            Assert::isTrue(types.contains(td), "contains(double) should be true");
            Assert::isFalse(types.contains(ArtifactType::of<char>()), "contains(char) should be false");
        }

        inline const static Test<void> artifact_types_initializer_list {
            "ArtifactTypes initializer_list deduplicates and supports contains()", testArtifactTypesInitializerListDedupAndContains
        };

        static void testArtifactTypesLogicalAndIsNonMutatingUnion()
        {
            const auto ti = ArtifactType::of<int>();
            const auto td = ArtifactType::of<double>();
            const auto tc = ArtifactType::of<char>();

            const ArtifactTypes left { ti, td };
            const ArtifactTypes right { td, tc };

            const ArtifactTypes combined = left && right;

            Assert::areEqual(std::size_t{3}, combined.size());
            Assert::isTrue(combined.contains(ti));
            Assert::isTrue(combined.contains(td));
            Assert::isTrue(combined.contains(tc));

            Assert::areEqual(std::size_t{2}, left.size());
            Assert::isTrue(left.contains(ti));
            Assert::isTrue(left.contains(td));
            Assert::isFalse(left.contains(tc));

            Assert::areEqual(std::size_t{2}, right.size());
            Assert::isFalse(right.contains(ti));
            Assert::isTrue(right.contains(td));
            Assert::isTrue(right.contains(tc));
        }

        inline const static Test<void> artifact_types_logical_and_non_mutating_union {
            "ArtifactTypes operator&& returns a new union without mutating operands", testArtifactTypesLogicalAndIsNonMutatingUnion
        };

        static void testArtifactTypeLogicalAndBuildsArtifactTypes()
        {
            const auto ti = ArtifactType::of<int>();
            const auto td = ArtifactType::of<double>();

            const ArtifactTypes types = ti && td;

            Assert::areEqual(std::size_t{2}, types.size());
            Assert::isTrue(types.contains(ti));
            Assert::isTrue(types.contains(td));
        }

        inline const static Test<void> artifact_type_logical_and_builds_types {
            "ArtifactType operator&& returns ArtifactTypes", testArtifactTypeLogicalAndBuildsArtifactTypes
        };
    };
}