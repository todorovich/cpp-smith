#include <iterator>
#include <utility>

#include "build/ProjectInterface.hpp"
#include "compile/model/factory/SharedLibraryFactory.hpp"

namespace cpp_smith
{
	SharedLibraryFactory::SharedLibraryFactory(ProjectInterface& parent, std::string name)
		: ArtifactFactory(parent)
		, _parent(parent)
		, _name(std::move(name))
	{}

	std::unique_ptr<SharedLibrary> SharedLibraryFactory::_create() const
	{
		return std::make_unique<SharedLibrary>(
			_parent,
			ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
			_dependencies,
			_sources
		);
	}

	SharedLibraryFactory& SharedLibraryFactory::addSource(std::filesystem::path source)
	{
		_sources.emplace_back(std::move(source));
		return *this;
	}

	SharedLibraryFactory& SharedLibraryFactory::addSources(std::vector<std::filesystem::path> sources)
	{
		_sources.insert(
			_sources.end(),
			std::make_move_iterator(sources.begin()),
			std::make_move_iterator(sources.end())
		);
		return *this;
	}

	SharedLibraryFactory& SharedLibraryFactory::addDependency(ArtifactCoordinates coordinates)
	{
		_dependencies.emplace_back(std::move(coordinates));
		return *this;
	}

	SharedLibraryFactory& SharedLibraryFactory::addDependencies(std::vector<ArtifactCoordinates> coordinates)
	{
		_dependencies.insert(
			_dependencies.end(),
			std::make_move_iterator(coordinates.begin()),
			std::make_move_iterator(coordinates.end())
		);
		return *this;
	}
}
