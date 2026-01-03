#pragma once

#include <concepts>
#include <string>

namespace cpp_smith
{
	class ProjectInterface;

	template <class T>
	struct Factory;

	template <class T>
	concept HasFactory = requires(ProjectInterface& project)
	{
		typename Factory<T>::factory;
		{ Factory<T>::create(project, std::string{"name"}) } -> std::same_as<typename Factory<T>::factory>;
		{ Factory<T>::create(project, std::string{"name"}).submit() } -> std::same_as<const T&>;
	};
}