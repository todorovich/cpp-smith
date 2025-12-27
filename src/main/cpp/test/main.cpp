#include "Tester.hpp"

int main()
{
    try {
        const auto [failures, test_results] = test::Tester::test();

        return failures;
    }
    catch (...)
    {
        return 1;
    }
}