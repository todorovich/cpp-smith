#pragma once

#include <initializer_list>
#include <span>
#include <unordered_set>
#include <vector>

#include "build/artifacts/TypeId.hpp"

namespace cpp_smith
{
	class TypeIdList;

	[[nodiscard]] TypeIdList operator&&(const TypeId left, const TypeId right);
	[[nodiscard]] TypeIdList operator&&(const TypeIdList& types, const TypeId type);
	[[nodiscard]] TypeIdList operator&&(const TypeId type, const TypeIdList& types);
	[[nodiscard]] TypeIdList operator&&(const TypeIdList& left, const TypeIdList& right);

	class TypeIdList final
	{
		std::unordered_set<TypeId> _artifact_types;

	public:
		TypeIdList() = default;

		explicit TypeIdList(const size_t size)
			: _artifact_types{ size }
		{}

		explicit TypeIdList(const std::initializer_list<TypeId> artifactList)
			: _artifact_types{ artifactList.begin(), artifactList.end() }
		{}

		explicit TypeIdList(const std::vector<TypeId>& types)
			: _artifact_types{ types.begin(), types.end() }
		{}

		explicit TypeIdList(const std::span<const TypeId> types)
			: _artifact_types{ types.begin(), types.end() }
		{}

		[[nodiscard]] bool contains(const TypeId keyArtifactType) const noexcept
		{
			return _artifact_types.contains(keyArtifactType);
		}

		[[nodiscard]] bool empty() const noexcept { return _artifact_types.empty(); }
		[[nodiscard]] std::size_t size() const noexcept { return _artifact_types.size(); }

		friend TypeIdList operator&&(const TypeId left, const TypeId right);
		friend TypeIdList operator&&(const TypeIdList& types, const TypeId type);
		friend TypeIdList operator&&(const TypeId type, const TypeIdList& types);
		friend TypeIdList operator&&(const TypeIdList& left, const TypeIdList& right);
	};

	inline TypeIdList operator&&(const TypeId left, const TypeId right)
	{
		return TypeIdList{ left, right };
	}

	inline TypeIdList operator&&(const TypeIdList& types, const TypeId type)
	{
		TypeIdList result {types.size() + 1 };
		result._artifact_types.emplace(type);
		result._artifact_types.insert(types._artifact_types.begin(), types._artifact_types.end());
		return result;
	}

	inline TypeIdList operator&&(const TypeId type, const TypeIdList& types)
	{
		return types && type;
	}

	inline TypeIdList operator&&(const TypeIdList& left, const TypeIdList& right)
	{
		TypeIdList result { left.size() + right.size() };
		result._artifact_types.insert(left._artifact_types.begin(), left._artifact_types.end());
		result._artifact_types.insert(right._artifact_types.begin(), right._artifact_types.end());
		return result;
	}
}