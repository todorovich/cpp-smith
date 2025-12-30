#include "Artifact.hpp"

#include "build/Project.hpp"

cpp_smith::Artifact::Artifact(
	Project& project,
	const ArtifactCoordinates& artifactCoordinate,
	const std::vector<ArtifactCoordinates>& dependencies,
	const ArtifactType& type
)
	: _artifact_coordinates{ artifactCoordinate }
 	, _dependencies{ dependencies }
 	, _types{ ArtifactType::of<Artifact>() && type }
 	, _parent(project)
{}

cpp_smith::Artifact::Artifact(
	Project& project,
	const ArtifactCoordinates& artifactCoordinate,
	const std::vector<ArtifactCoordinates>& dependencies,
	const ArtifactTypes& types
)
	: _artifact_coordinates{ artifactCoordinate }
 	, _dependencies{ dependencies }
 	, _types{ ArtifactType::of<Artifact>() && types }
 	, _parent(project)
{}
