#include "Prover.hpp"

int main()
{
    try {
        const auto [failures, test_results] = prover::Prover::test();

        return failures;
    }
    catch (...)
    {
        return 1;
    }
}