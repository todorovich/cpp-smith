#include "compile/model/factory/StaticLibraryFactory.hpp"

#include <iterator>
#include <utility>

namespace cpp_smith
{
	StaticLibraryFactory::StaticLibraryFactory(ProjectInterface& parent, std::string name)
		: ArtifactFactory(parent)
		, _parent(parent)
		, _name(std::move(name))
	{}

	std::unique_ptr<StaticLibrary> StaticLibraryFactory::_create() const
	{
		return std::make_unique<StaticLibrary>(
			_parent,
			ArtifactCoordinates{ _parent.getProjectCoordinates(), _name },
			_dependencies,
			_sources
		);
	}

	StaticLibraryFactory& StaticLibraryFactory::addSource(std::filesystem::path source)
	{
		_sources.emplace_back(std::move(source));
		return *this;
	}

	StaticLibraryFactory& StaticLibraryFactory::addSources(std::vector<std::filesystem::path> sources)
	{
		_sources.insert(
			_sources.end(),
			std::make_move_iterator(sources.begin()),
			std::make_move_iterator(sources.end())
		);
		return *this;
	}

	StaticLibraryFactory& StaticLibraryFactory::addDependency(ArtifactCoordinates coordinates)
	{
		_dependencies.emplace_back(std::move(coordinates));
		return *this;
	}

	StaticLibraryFactory& StaticLibraryFactory::addDependencies(std::vector<ArtifactCoordinates> coordinates)
	{
		_dependencies.insert(
			_dependencies.end(),
			std::make_move_iterator(coordinates.begin()),
			std::make_move_iterator(coordinates.end())
		);
		return *this;
	}
}