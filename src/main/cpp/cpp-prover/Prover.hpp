#pragma once

#include "TestResult.hpp"
#include "../cpp-smith/TransparentContainers.hpp"

#include <string>
#include <vector>

namespace prover
{
    struct TestResults
    {
        int failures;
        // { Test Name, Test Output }
        TransparentUnorderedMap<std::string, std::string> results;
    };

    struct Prover
    {
        static std::pair<int, std::vector<TestResult>> test();
    };
}
