#include "test/Test.hpp"

#include "build/artifacts/ArtifactType.hpp"
#include "build/artifacts/Executable.hpp"
#include "build/artifacts/StaticLibrary.hpp"
#include "build/artifacts/SharedLibrary.hpp"

#include <string>

namespace test
{
    using namespace test;
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        struct A {};
        struct B {};
        template <int N>
        struct Tag {};

        static void testArtifactTypeEquality()
        {
            const auto t1 = ArtifactType::of<int>();
            const auto t2 = ArtifactType::of<int>();
            const auto t3 = ArtifactType::of<double>();

            Assert::isTrue(t1 == t2, "same T should produce equal ArtifactType");
            Assert::isFalse(t1 == t3, "different T should produce different ArtifactType");
        }

        inline const static Test<void> artifact_type_equality {
            "ArtifactType::of<T>() equality/inequality", testArtifactTypeEquality
        };

        static void testArtifactTypeDistinctUserTypes()
        {
            Assert::isFalse(
                ArtifactType::of<A>() == ArtifactType::of<B>(),
                "distinct user-defined types should be different ArtifactType values"
            );

            Assert::isFalse(
                ArtifactType::of<Tag<1>>() == ArtifactType::of<Tag<2>>(),
                "different template specializations should be different ArtifactType values"
            );
        }

        inline const static Test<void> artifact_type_distinct_user_types {
            "ArtifactType distinguishes distinct types", testArtifactTypeDistinctUserTypes
        };

        static void testArtifactTypeNonPrimitiveTypes()
        {
            Assert::isTrue(
                ArtifactType::of<std::string>() == ArtifactType::of<std::string>(),
                "non-primitive (std::string) should be stable"
            );

            Assert::isTrue(
                ArtifactType::of<Executable>() == ArtifactType::of<Executable>(),
                "Executable type id should be stable"
            );

            Assert::isFalse(
                ArtifactType::of<Executable>() == ArtifactType::of<StaticLibrary>(),
                "Executable and StaticLibrary must have different type ids"
            );

            Assert::isFalse(
                ArtifactType::of<SharedLibrary>() == ArtifactType::of<StaticLibrary>(),
                "SharedLibrary and StaticLibrary must have different type ids"
            );
        }

        inline const static Test<void> artifact_type_non_primitive_types {
            "ArtifactType works with non-primitive types", testArtifactTypeNonPrimitiveTypes
        };

        static void testArtifactTypeConstexpr()
        {
            constexpr auto ti = ArtifactType::of<int>();
            static_assert(ti == ArtifactType::of<int>());
            static_assert(!(ti == ArtifactType::of<double>()));

            Assert::isTrue(ti == ArtifactType::of<int>());
            Assert::isFalse(ti == ArtifactType::of<double>());
        }

        inline const static Test<void> artifact_type_constexpr {
            "ArtifactType::of<T>() is constexpr-friendly", testArtifactTypeConstexpr
        };
    };
}