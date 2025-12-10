#pragma once

#include "Logger.hpp"
#include "TestResult.hpp"

#include <string>
#include <source_location>

namespace prover
{
    class TestInterface
    {
    public:
        const std::string name;
        const std::source_location source_location;
        logging::Logger logger;

        explicit TestInterface(
            const std::string_view name,
            const std::source_location& source_location,
            logging::Logger _logger
        )
            : name(name)
            , source_location(source_location)
            , logger(std::move(_logger))
        {}

        virtual ~TestInterface() = default;

        virtual std::pair<int, std::vector<TestResult>> test() noexcept = 0;

        virtual std::string_view output() const = 0;
    };
}