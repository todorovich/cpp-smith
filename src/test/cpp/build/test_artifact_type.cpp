#include "test/Test.hpp"

#include "build/artifacts/TypeId.hpp"
#include "compile/model/Executable.hpp"
#include "compile/model/StaticLibrary.hpp"
#include "compile/model/SharedLibrary.hpp"

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
            const auto t1 = TypeId::of<int>();
            const auto t2 = TypeId::of<int>();
            const auto t3 = TypeId::of<double>();

            Assert::isTrue(t1 == t2, "same T should produce equal ArtifactType");
            Assert::isFalse(t1 == t3, "different T should produce different ArtifactType");
        }

        inline const static Test<void> artifact_type_equality {
            "ArtifactType::of<T>() equality/inequality", testArtifactTypeEquality
        };

        static void testArtifactTypeDistinctUserTypes()
        {
            Assert::isFalse(
                TypeId::of<A>() == TypeId::of<B>(),
                "distinct user-defined types should be different ArtifactType values"
            );

            Assert::isFalse(
                TypeId::of<Tag<1>>() == TypeId::of<Tag<2>>(),
                "different template specializations should be different ArtifactType values"
            );
        }

        inline const static Test<void> artifact_type_distinct_user_types {
            "ArtifactType distinguishes distinct types", testArtifactTypeDistinctUserTypes
        };

        static void testArtifactTypeNonPrimitiveTypes()
        {
            Assert::isTrue(
                TypeId::of<std::string>() == TypeId::of<std::string>(),
                "non-primitive (std::string) should be stable"
            );

            Assert::isTrue(
                TypeId::of<Executable>() == TypeId::of<Executable>(),
                "Executable type id should be stable"
            );

            Assert::isFalse(
                TypeId::of<Executable>() == TypeId::of<StaticLibrary>(),
                "Executable and StaticLibrary must have different type ids"
            );

            Assert::isFalse(
                TypeId::of<SharedLibrary>() == TypeId::of<StaticLibrary>(),
                "SharedLibrary and StaticLibrary must have different type ids"
            );
        }

        inline const static Test<void> artifact_type_non_primitive_types {
            "ArtifactType works with non-primitive types", testArtifactTypeNonPrimitiveTypes
        };

        static void testArtifactTypeConstexpr()
        {
            constexpr auto ti = TypeId::of<int>();
            static_assert(ti == TypeId::of<int>());
            static_assert(!(ti == TypeId::of<double>()));

            Assert::isTrue(ti == TypeId::of<int>());
            Assert::isFalse(ti == TypeId::of<double>());
        }

        inline const static Test<void> artifact_type_constexpr {
            "ArtifactType::of<T>() is constexpr-friendly", testArtifactTypeConstexpr
        };
    };
}