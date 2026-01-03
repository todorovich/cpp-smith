#pragma once

#include <filesystem>
#include <memory>

#include "artifacts/ArtifactCoordinates.hpp"

namespace cpp_smith
{
	class Artifact;
	class Configuration;
	class Project;

	class ProjectInterface
	{
	public:
		virtual ~ProjectInterface() = default;

		virtual Project& accept(std::unique_ptr<Artifact> artifact) = 0;
		virtual Project& accept(std::unique_ptr<Configuration> configuration) = 0;

		using ArtifactMap = std::unordered_map<ArtifactCoordinates, std::unique_ptr<Artifact>>;

		[[nodiscard]] virtual const Artifact& getArtifact(const std::string& name) const = 0;
		[[nodiscard]] virtual const Artifact& getArtifact(const ArtifactCoordinates& artifactCoordinates) const = 0;
		[[nodiscard]] virtual const ArtifactMap& getArtifacts() const = 0;

		[[nodiscard]] virtual const Configuration& getConfiguration(const std::string& name) const = 0;

		[[nodiscard]] virtual const ProjectCoordinates& getProjectCoordinates() const = 0;
		[[nodiscard]] virtual const std::filesystem::path& getProjectDirectory() const = 0;
	};
}
