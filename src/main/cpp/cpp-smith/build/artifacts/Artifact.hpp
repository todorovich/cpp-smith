#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace cpp_smith
{
    class Artifact
    {
        std::string _name;

    protected:
        explicit Artifact(std::string name)
            : _name(std::move(name)) {}

    public:
        virtual ~Artifact() = default;

        [[nodiscard]] const std::string& name() const { return _name; }

        // Return the translation units that define this artifact.
        [[nodiscard]] virtual std::vector<std::filesystem::path> sourceFiles() const = 0;
    };
}
