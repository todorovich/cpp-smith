#pragma once

#include "../Project.hpp"
#include "ArtifactBuilder.hpp"
#include "SharedLibrary.hpp"

#include <filesystem>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace cpp_smith
{
    // Builder specialization for SharedLibrary
    template <>
    class ArtifactBuilder<SharedLibrary>
    {
        Project& _parent;
        std::string _name;
        std::vector<std::filesystem::path> _sources;

    public:
        ArtifactBuilder(Project& parent, std::string name)
            : _parent(parent)
            , _name(std::move(name))
        {}

        ArtifactBuilder& addSource(std::filesystem::path source)
        {
            _sources.emplace_back(std::move(source));
            return *this;
        }

        ArtifactBuilder& addSources(std::vector<std::filesystem::path> sources)
        {
            _sources.insert(
                _sources.end(),
                std::make_move_iterator(sources.begin()),
                std::make_move_iterator(sources.end())
            );

            return *this;
        }

        [[nodiscard]] std::unique_ptr<SharedLibrary> create() const
        {
            return std::make_unique<SharedLibrary>(_name, _sources);
        }

        [[maybe_unused]] Project& submit();
    };
}
