#include <iterator>
#include <utility>

#include "build/builders/ExecutableBuilder.hpp"

namespace cpp_smith
{
	ArtifactBuilder<Executable>::ArtifactBuilder(ProjectInterface& parent, std::string name)
		: ArtifactBuilderBase(parent)
		, _name(std::move(name))
		, _parent(parent)
	{}

	std::unique_ptr<Executable> ArtifactBuilder<Executable>::_create() const
	{
		return std::make_unique<Executable>(
			_parent,
			ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
			_dependencies,
			_sources
		);
	}

	ArtifactBuilder<Executable>& ArtifactBuilder<Executable>::addSource(std::filesystem::path source)
	{
		_sources.emplace_back(std::move(source));
		return *this;
	}

	ArtifactBuilder<Executable>& ArtifactBuilder<Executable>::addSources(std::vector<std::filesystem::path> sources)
	{
		_sources.insert(
			_sources.end(),
			std::make_move_iterator(sources.begin()),
			std::make_move_iterator(sources.end())
		);
		return *this;
	}

	ArtifactBuilder<Executable>& ArtifactBuilder<Executable>::addDependency(ArtifactCoordinates coordinates)
	{
		_dependencies.emplace_back(std::move(coordinates));
		return *this;
	}

	ArtifactBuilder<Executable>& ArtifactBuilder<Executable>::addDependencies(std::vector<ArtifactCoordinates> coordinates)
	{
		_dependencies.insert(
			_dependencies.end(),
			std::make_move_iterator(coordinates.begin()),
			std::make_move_iterator(coordinates.end())
		);
		return *this;
	}
}