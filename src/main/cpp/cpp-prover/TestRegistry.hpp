#pragma once

#include "TestInterface.hpp"

#include <vector>

namespace prover
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

        [[nodiscard]] const std::vector<TestInterface*>& all() const
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