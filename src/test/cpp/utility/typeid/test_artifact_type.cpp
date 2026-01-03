#include "test/Test.hpp"

#include <string>

#include "compile/model/Executable.hpp"
#include "compile/model/StaticLibrary.hpp"
#include "compile/model/SharedLibrary.hpp"
#include "typeid/TypeId.hpp"

namespace test
{
    using namespace test;
    using namespace cpp_smith;

    struct Tests
    {
        Tests() = delete;

        static void testArtifactTypeEquality()
        {
            constexpr auto t1 = TypeId::of<int>();
            constexpr auto t2 = TypeId::of<int>();
            constexpr auto t3 = TypeId::of<double>();

            Assert::isTrue(t1 == t2, "same T should produce equal ArtifactType");
            Assert::isFalse(t1 == t3, "different T should produce different ArtifactType");
        }

        static void testArtifactTypeNonPrimitiveTypes()
        {
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
            static_assert(ti != TypeId::of<double>());

            Assert::isTrue(ti == TypeId::of<int>());
            Assert::isFalse(ti == TypeId::of<double>());
        }

        inline const static Test<void> artifact_type_constexpr {
            "ArtifactType::of<T>() is constexpr-friendly", testArtifactTypeConstexpr
        };
    };
}