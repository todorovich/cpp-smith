#include <string>
#include <vector>

#include "test/Assert.hpp"
#include "test/Test.hpp"

namespace test
{
    struct Tests
    {
        inline static std::vector<std::string> executed{};

        static void assert_prefix(const std::vector<std::string>& expected)
        {
            Assert::areEqual(expected.size(), executed.size());
            for (std::size_t i = 0; i < expected.size(); ++i)
            {
                Assert::areEqual(expected[i], executed[i]);
            }
        }

        static void test_a()
        {
            assert_prefix({"D", "B", "E", "C", "F", "G", "H"});
            executed.emplace_back("A");
        }

        static void test_b()
        {
            assert_prefix({"D"});
            executed.emplace_back("B");
        }

        static void test_c()
        {
            assert_prefix({"D", "B", "E"});
            executed.emplace_back("C");
        }

        static void test_d()
        {
            executed.clear();
            executed.emplace_back("D");
        }

        static void test_e()
        {
            assert_prefix({"D", "B"});
            executed.emplace_back("E");
        }

        static void test_f()
        {
            assert_prefix({"D", "B", "E", "C"});
            executed.emplace_back("F");
        }

        static void test_g()
        {
            assert_prefix({"D", "B", "E", "C", "F"});
            executed.emplace_back("G");
        }

        static void test_h()
        {
            assert_prefix({"D", "B", "E", "C", "F", "G"});
            executed.emplace_back("H");
        }

        Test<void> A;
        Test<void> B;
        Test<void> C;
        Test<void> D;
        Test<void> E;
        Test<void> F;
        Test<void> G;
        Test<void> H;

        Tests()
            : A("Ordered Test: A", test_a, std::vector<TestInterface*>{ &H })
            , B("Ordered Test: B", test_b, std::vector<TestInterface*>{ &D })
            , C("Ordered Test: C", test_c, std::vector<TestInterface*>{ &E })
            , D("Ordered Test: D", test_d)
            , E("Ordered Test: E", test_e, std::vector<TestInterface*>{ &B })
            , F("Ordered Test: F", test_f, std::vector<TestInterface*>{ &C })
            , G("Ordered Test: G", test_g, std::vector<TestInterface*>{ &F })
            , H("Ordered Test: H", test_h, std::vector<TestInterface*>{ &G })
        {}
    };

    inline const static Tests tests {};
}