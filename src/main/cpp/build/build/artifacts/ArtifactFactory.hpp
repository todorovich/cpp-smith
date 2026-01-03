#pragma once

#include <memory>

#include "build/ProjectInterface.hpp"

namespace cpp_smith
{
	class Artifact;

	template <typename T>
	concept ArtifactTypeConcept = std::derived_from<T, Artifact>;

	template<ArtifactTypeConcept T>
	class ArtifactFactory
	{
		ProjectInterface& _project;

	protected:
		explicit ArtifactFactory(ProjectInterface& project)
			: _project(project)
		{};

		[[nodiscard]] virtual std::unique_ptr<T> _create() const = 0;

	public:
		virtual ~ArtifactFactory() = default;

		const T& submit()
		{
			auto unique_ptr = _create();

			auto& artifact = *unique_ptr.get();

			_project.accept(std::move(unique_ptr));

			return artifact;
		}
	};
}