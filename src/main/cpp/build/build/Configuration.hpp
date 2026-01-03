#pragma once
#include "artifacts/IdentifiedType.hpp"

namespace cpp_smith
{
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
