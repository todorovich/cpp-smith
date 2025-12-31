// src/main/cpp/build/build/builders/StaticLibraryBuilder.cpp
#include "build/builders/StaticLibraryBuilder.hpp"

#include <iterator>
#include <utility>

namespace cpp_smith
{
	ArtifactBuilder<StaticLibrary>::ArtifactBuilder(ProjectInterface& parent, std::string name)
		: ArtifactBuilderBase(parent)
		, _parent(parent)
		, _name(std::move(name))
	{}

	std::unique_ptr<StaticLibrary> ArtifactBuilder<StaticLibrary>::_create() const
	{
		return std::make_unique<StaticLibrary>(
			_parent,
			ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
			_dependencies,
			_sources
		);
	}

	ArtifactBuilder<StaticLibrary>& ArtifactBuilder<StaticLibrary>::addSource(std::filesystem::path source)
	{
		_sources.emplace_back(std::move(source));
		return *this;
	}

	ArtifactBuilder<StaticLibrary>& ArtifactBuilder<StaticLibrary>::addSources(std::vector<std::filesystem::path> sources)
	{
		_sources.insert(
			_sources.end(),
			std::make_move_iterator(sources.begin()),
			std::make_move_iterator(sources.end())
		);
		return *this;
	}

	ArtifactBuilder<StaticLibrary>& ArtifactBuilder<StaticLibrary>::addDependency(ArtifactCoordinates coordinates)
	{
		_dependencies.emplace_back(std::move(coordinates));
		return *this;
	}

	ArtifactBuilder<StaticLibrary>& ArtifactBuilder<StaticLibrary>::addDependencies(std::vector<ArtifactCoordinates> coordinates)
	{
		_dependencies.insert(
			_dependencies.end(),
			std::make_move_iterator(coordinates.begin()),
			std::make_move_iterator(coordinates.end())
		);
		return *this;
	}
}