#pragma once

#include <filesystem>
#include <memory>

#include "artifacts/ArtifactCoordinates.hpp"

namespace cpp_smith
{
	class Artifact;
	class Configuration;
	class ProjectCoordinates;

	class ProjectInterface
	{
	public:
		virtual ~ProjectInterface() = default;

		// Registration hooks used by builders
		virtual ProjectInterface& accept(std::unique_ptr<Artifact> artifact) = 0;
		virtual ProjectInterface& accept(Configuration&& config) = 0;

		// Context that builders/artifacts may need
		[[nodiscard]] virtual const ProjectCoordinates& getProjectCoordinates() const = 0;
		[[nodiscard]] virtual const std::filesystem::path& getProjectDirectory() const = 0;
		[[nodiscard]] virtual const Artifact& getArtifact(const std::string& name) const = 0;
		[[nodiscard]] virtual const Artifact& getArtifact(const ArtifactCoordinates& artifactCoordinates) const = 0;
		[[nodiscard]] virtual
		const std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>>& getArtifacts() const = 0;
	};
}
