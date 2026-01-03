#pragma once

#include "TestResult.hpp"
#include "../../utility/containers/containers/TransparentContainers.hpp"

#include <string>
#include <vector>

namespace test
{
    struct TestResults
    {
        int failures;

        // { Test Name, Test Output }
        TransparentUnorderedMap<std::string, std::string> results;
    };

    struct Tester
    {
        static std::pair<int, std::vector<TestResult>> test();
    };
}
