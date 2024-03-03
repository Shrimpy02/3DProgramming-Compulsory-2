#include "DefaultPlane.h"
#include "Shader.h"

DefaultPlane::DefaultPlane()
{
}

DefaultPlane::DefaultPlane(Shader* _shader, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

void DefaultPlane::Initialize()
{
	Geometry::Initialize(&PlaneVertices, NumVariables);
}

void DefaultPlane::drawVertexGeometry()
{
	if (ObjectShader)
	{
		ObjectShader->use();
		ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
	}

	Geometry::drawVertexGeometry();
}


void DefaultPlane::TickVertexGeometry()
{

}
