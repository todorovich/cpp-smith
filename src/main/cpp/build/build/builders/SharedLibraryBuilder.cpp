
#include "build/builders/SharedLibraryBuilder.hpp"

#include <iterator>
#include <utility>

#include "build/ProjectInterface.hpp"

namespace cpp_smith
{
	ArtifactBuilder<SharedLibrary>::ArtifactBuilder(ProjectInterface& parent, std::string name)
		: ArtifactBuilderBase(parent)
		, _parent(parent)
		, _name(std::move(name))
	{}

	std::unique_ptr<SharedLibrary> ArtifactBuilder<SharedLibrary>::_create() const
	{
		return std::make_unique<SharedLibrary>(
			_parent,
			ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
			_dependencies,
			_sources
		);
	}

	ArtifactBuilder<SharedLibrary>& ArtifactBuilder<SharedLibrary>::addSource(std::filesystem::path source)
	{
		_sources.emplace_back(std::move(source));
		return *this;
	}

	ArtifactBuilder<SharedLibrary>& ArtifactBuilder<SharedLibrary>::addSources(std::vector<std::filesystem::path> sources)
	{
		_sources.insert(
			_sources.end(),
			std::make_move_iterator(sources.begin()),
			std::make_move_iterator(sources.end())
		);
		return *this;
	}

	ArtifactBuilder<SharedLibrary>& ArtifactBuilder<SharedLibrary>::addDependency(ArtifactCoordinates coordinates)
	{
		_dependencies.emplace_back(std::move(coordinates));
		return *this;
	}

	ArtifactBuilder<SharedLibrary>& ArtifactBuilder<SharedLibrary>::addDependencies(std::vector<ArtifactCoordinates> coordinates)
	{
		_dependencies.insert(
			_dependencies.end(),
			std::make_move_iterator(coordinates.begin()),
			std::make_move_iterator(coordinates.end())
		);
		return *this;
	}
}
