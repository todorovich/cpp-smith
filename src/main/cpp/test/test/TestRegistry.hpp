#pragma once

#include "TestInterface.hpp"

#include <vector>

namespace test
{
    class TestRegistry
    {
        std::vector<TestInterface*> tests;

        TestRegistry() = default;

    public:
        static TestRegistry& instance();

        void add(TestInterface* t)
        {
            tests.push_back(t);
        }

        [[nodiscard]] std::vector<TestInterface*>& all()
        {
            return tests;
        }
    };

    inline TestRegistry& TestRegistry::instance()
    {
        static TestRegistry registry; // NOSONAR
        return registry;
    }
}