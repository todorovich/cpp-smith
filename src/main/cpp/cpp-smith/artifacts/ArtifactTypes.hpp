#pragma once

#include <initializer_list>
#include <span>
#include <unordered_set>
#include <vector>

#include "ArtifactType.hpp"

namespace cpp_smith
{
	class ArtifactTypes;

	[[nodiscard]] ArtifactTypes operator&&(const ArtifactType left, const ArtifactType right);
	[[nodiscard]] ArtifactTypes operator&&(const ArtifactTypes& types, const ArtifactType type);
	[[nodiscard]] ArtifactTypes operator&&(const ArtifactType type, const ArtifactTypes& types);
	[[nodiscard]] ArtifactTypes operator&&(const ArtifactTypes& left, const ArtifactTypes& right);

	class ArtifactTypes final
	{
		std::unordered_set<ArtifactType> _artifact_types;

	public:
		ArtifactTypes() = default;

		explicit ArtifactTypes(const size_t size)
			: _artifact_types{ size }
		{}

		explicit ArtifactTypes(const std::initializer_list<ArtifactType> artifactList)
			: _artifact_types{ artifactList.begin(), artifactList.end() }
		{}

		explicit ArtifactTypes(const std::vector<ArtifactType>& types)
			: _artifact_types{ types.begin(), types.end() }
		{}

		explicit ArtifactTypes(const std::span<const ArtifactType> types)
			: _artifact_types{ types.begin(), types.end() }
		{}

		[[nodiscard]] bool contains(const ArtifactType keyArtifactType) const noexcept
		{
			return _artifact_types.contains(keyArtifactType);
		}

		[[nodiscard]] bool empty() const noexcept { return _artifact_types.empty(); }
		[[nodiscard]] std::size_t size() const noexcept { return _artifact_types.size(); }

		friend ArtifactTypes operator&&(const ArtifactType left, const ArtifactType right);
		friend ArtifactTypes operator&&(const ArtifactTypes& types, const ArtifactType type);
		friend ArtifactTypes operator&&(const ArtifactType type, const ArtifactTypes& types);
		friend ArtifactTypes operator&&(const ArtifactTypes& left, const ArtifactTypes& right);
	};

	inline ArtifactTypes operator&&(const ArtifactType left, const ArtifactType right)
	{
		return ArtifactTypes{ left, right };
	}

	inline ArtifactTypes operator&&(const ArtifactTypes& types, const ArtifactType type)
	{
		ArtifactTypes result {types.size() + 1 };
		result._artifact_types.emplace(type);
		result._artifact_types.insert(types._artifact_types.begin(), types._artifact_types.end());
		return result;
	}

	inline ArtifactTypes operator&&(const ArtifactType type, const ArtifactTypes& types)
	{
		return types && type;
	}

	inline ArtifactTypes operator&&(const ArtifactTypes& left, const ArtifactTypes& right)
	{
		ArtifactTypes result { left.size() + right.size() };
		result._artifact_types.insert(left._artifact_types.begin(), left._artifact_types.end());
		result._artifact_types.insert(right._artifact_types.begin(), right._artifact_types.end());
		return result;
	}
}