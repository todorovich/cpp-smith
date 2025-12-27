#pragma once

#include "Project.hpp"
#include "ArtifactBuilder.hpp"

namespace cpp_smith
{
	template<ArtifactTypeConcept T>
	class ArtifactBuilderBase
	{
		Project& _project;

	protected:
		explicit ArtifactBuilderBase(Project& project)
			: _project(project)
		{};

		[[nodiscard]] virtual std::unique_ptr<T> _create() const = 0;

	public:
		virtual ~ArtifactBuilderBase() = default;

		T* submit()
		{
			auto unique_ptr = _create();
			auto* ptr = unique_ptr.get();

			_project.accept(std::move(unique_ptr));

			return ptr;
		}
	};
}