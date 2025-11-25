#pragma once

#include "TestInterface.hpp"
#include "TestRegistry.hpp"
#include "Assert.hpp"

#include <functional>
#include <tuple>

namespace prover
{
    template <typename ReturnType, typename... Args>
    class Test final : public TestInterface
    {
        std::function<ReturnType(Args...)> _test_function;
        std::vector<std::tuple<Args...>> _arguments;
        std::source_location _source_location;

    public:
        using Assert = prover::Assert;

        Test(
            const std::string_view& name,
            std::function<ReturnType(Args...)> test_function,
            std::vector<std::tuple<Args...>> _args = {},
            std::source_location source_location = std::source_location::current()
        )
            : TestInterface(name, source_location)
            , _test_function(std::move(test_function))
            , _arguments(std::move(_args))
        {
            TestRegistry::instance().add(this);
        }

        void test() const override
        {
            if constexpr (sizeof...(Args) == 0)
            {
                _test_function();
            }
            else
            {
                for (auto& arg : _arguments)
                {
                    std::apply(_test_function, arg);
                }
            }
        }
    };
}