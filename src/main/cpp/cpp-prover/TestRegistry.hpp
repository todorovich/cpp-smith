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
        static TestRegistry& instance()
        {
            static TestRegistry r;
            return r;
        }

        void add(TestInterface* t)
        {
            tests.push_back(t);
        }

        const std::vector<TestInterface*>& all() const
        {
            return tests;
        }
    };
}