#pragma once

#include "Prover.hpp"
#include "Test.hpp"

using prover::Assert;

int main()
{
    try {
        return prover::Prover{}.test();
    }
    catch (...)
    {
        return 1;
    }
}