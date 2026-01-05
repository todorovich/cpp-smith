#include <string>
#include <vector>

#include "test/Assert.hpp"
#include "test/Test.hpp"

namespace test
{
    inline const static struct Tests
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
            executed.push_back("A");
        }

        static void test_b()
        {
            assert_prefix({"D"});
            executed.push_back("B");
        }

        static void test_c()
        {
            assert_prefix({"D", "B", "E"});
            executed.push_back("C");
        }

        static void test_d()
        {
            executed.clear();
            executed.push_back("D");
        }

        static void test_e()
        {
            assert_prefix({"D", "B"});
            executed.push_back("E");
        }

        static void test_f()
        {
            assert_prefix({"D", "B", "E", "C"});
            executed.push_back("F");
        }

        static void test_g()
        {
            assert_prefix({"D", "B", "E", "C", "F"});
            executed.push_back("G");
        }

        static void test_h()
        {
            assert_prefix({"D", "B", "E", "C", "F", "G"});
            executed.push_back("H");
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
    } tests {};
}