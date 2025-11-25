#pragma once

namespace prover
{
    class TestInterface
    {
    public:
        const std::string name;
        const std::source_location source_location;

        explicit TestInterface(std::string_view name, const std::source_location& source_location)
            : name(name)
            , source_location(source_location)
        {}

        virtual ~TestInterface() = default;

        virtual void test() const = 0;
    };
}