#include "DefaultPyramid.h"
#include "Shader.h"

DefaultPyramid::DefaultPyramid()
{
}

DefaultPyramid::DefaultPyramid(Shader* _shader, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees,
	vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

void DefaultPyramid::Initialize()
{
	Geometry::Initialize(&PyramidVertices, NumVariables);
}

void DefaultPyramid::drawVertexGeometry()
{
	if (ObjectShader)
	{
		ObjectShader->use();
		ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
	}

	Geometry::drawVertexGeometry();
}

void DefaultPyramid::TickVertexGeometry()
{
	
}