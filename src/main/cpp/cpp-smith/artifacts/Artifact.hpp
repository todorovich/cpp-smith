#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace cpp_smith
{
    class Configuration;
    class CompilerProbe;

    class Artifact
    {
        std::string _name;

      protected:
        explicit Artifact(std::string name)
            : _name(std::move(name))
        {}

      public:
        virtual ~Artifact() = default;

        [[nodiscard]] const std::string& name() const { return _name; }

        // Return the translation units that define this artifact.
        [[nodiscard]] virtual const std::vector<std::filesystem::path>& sources() const = 0;

        virtual void build(
            const Configuration* configuration,
            const std::filesystem::path& build_directory,
            const std::filesystem::path& install_directory
        ) const = 0;
    };
}
