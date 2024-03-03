#include "ComplexGeometry.h"
#include "Shader.h"

ComplexGeometry::ComplexGeometry()
{
}

ComplexGeometry::ComplexGeometry(const char* _filePath, Shader* _shader, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
	FilePath = _filePath;
}

void ComplexGeometry::Initialize()
{
	Geometry::Initialize(InitializeVertexGeometryFromFile(FilePath),9);
}

void ComplexGeometry::drawVertexGeometry()
{
	if (ObjectShader)
	{
		ObjectShader->use();
		ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
	}

	Geometry::drawVertexGeometry();
}

void ComplexGeometry::TickVertexGeometry()
{
}
