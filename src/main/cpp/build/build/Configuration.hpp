#pragma once

#include "typeid/IdentifiedType.hpp"

namespace cpp_smith
{
	class Configuration;

	template<>
	struct TypeKey<Configuration>
	{
		static constexpr std::string_view value = "cpp_smith::Configuration";
	};

	class Configuration : public IdentifiedType
	{
	  protected:
		std::string _name;

		explicit Configuration(const std::string& name, const TypeId& type)
			: IdentifiedType(TypeId::of<Configuration>() && type)
			, _name(name)
		{}

		explicit Configuration(const std::string& name, const TypeIdList& types)
			: IdentifiedType(TypeId::of<Configuration>() && types)
			, _name(name)
		{}

	  public:
		const std::string& getName() const { return _name; }
	};
}
