#pragma once

#include "../BuildSystem.hpp"
#include "ArtifactBuilder.hpp"
#include "Executable.hpp"

#include <filesystem>
#include <memory>
#include <string>

namespace cpp_smith
{
    // Builder specialization for Executable
    template <>
    class ArtifactBuilder<Executable>
    {
        BuildSystem& _parent;
        std::string _name;
        std::filesystem::path _entry_point;

    public:
        ArtifactBuilder(BuildSystem& parent, std::string name)
            : _parent(parent)
            , _name(std::move(name))
        {}

        ArtifactBuilder& entryPoint(std::filesystem::path path)
        {
            _entry_point = std::move(path);
            return *this;
        }

        [[nodiscard]] std::unique_ptr<Executable> build() const
        {
            return std::make_unique<Executable>(_name, _entry_point);
        }

        [[maybe_unused]] BuildSystem& buildSystem();
    };
}