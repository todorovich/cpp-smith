#pragma once

#include <filesystem>
#include <string>
#include <vector>

class ArtifactBase
{
    const std::string _name;

protected:
    explicit ArtifactBase(std::string name);

public:
    virtual ~ArtifactBase() = default;

    [[nodiscard]] const std::string& name() const;

    // Returns the translation units (source files) defining this artifact
    [[nodiscard]] virtual std::vector<std::filesystem::path> sourceFiles() const = 0;
};
