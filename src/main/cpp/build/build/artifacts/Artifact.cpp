#include "Artifact.hpp"

#include "build/Project.hpp"

cpp_smith::Artifact::Artifact(
	ProjectInterface& project,
	const ArtifactCoordinates& artifactCoordinate,
	const std::vector<ArtifactCoordinates>& dependencies,
	const TypeId& type
)
	: IdentifiedType(TypeId::of<Artifact>() && type)
	, _artifact_coordinates{ artifactCoordinate }
 	, _dependencies{ dependencies }
 	, _parent(project)
{}

cpp_smith::Artifact::Artifact(
	ProjectInterface& project,
	const ArtifactCoordinates& artifactCoordinate,
	const std::vector<ArtifactCoordinates>& dependencies,
	const TypeIdList& types
)
	: IdentifiedType(TypeId::of<Artifact>() && types)
	, _artifact_coordinates{ artifactCoordinate }
 	, _dependencies{ dependencies }
 	, _parent(project)
{}
