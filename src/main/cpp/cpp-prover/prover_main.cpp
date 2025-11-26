#include "Prover.hpp"

int main()
{
    try {
        return prover::Prover::test();
    }
    catch (...)
    {
        return 1;
    }
}