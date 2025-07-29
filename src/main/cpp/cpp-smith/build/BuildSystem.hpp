#pragma once

#include "Configuration.hpp"
#include "ConfigurationBuilder.hpp"

#include <string>
#include <unordered_map>

class BuildSystem
{
    std::unordered_map<std::string, Configuration> _configurations;

public:
    // Start building a new configuration
    ConfigurationBuilder configuration(const std::string& name);

    // Finalize and store a Configuration
    BuildSystem& add(Configuration config);

    // Lookup or inspect configs (optional)
    const Configuration& getConfiguration(const std::string& name) const;
    const std::unordered_map<std::string, Configuration>& configurations() const;

    // Final entry point
    void build(); // optional: resolve graph, validate, etc.
};
