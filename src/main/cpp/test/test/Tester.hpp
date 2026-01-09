#pragma once

#include "TestResult.hpp"
#include "../../utility/containers/containers/TransparentContainers.hpp"

#include <string>
#include <vector>

#include "log/Logger.hpp"

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
        inline static logging::Logger log = logging::Logger::defaultLogger("Tester");

        static std::pair<int, std::vector<TestResult>> test();
    };
}
