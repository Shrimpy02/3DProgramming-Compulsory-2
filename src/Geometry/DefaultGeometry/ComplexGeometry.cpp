// Class includes
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

ComplexGeometry::~ComplexGeometry()
{
	Geometry::~Geometry();
}

void ComplexGeometry::Initialize()
{
	Geometry::Initialize(InitializeVertexGeometryFromFile(FilePath),9);
}

void ComplexGeometry::BeginPlayGeometry()
{
	Geometry::BeginPlayGeometry();
}

void ComplexGeometry::TickVertexGeometry(float deltatime)
{
	Geometry::TickVertexGeometry(deltatime);
}

bool ComplexGeometry::CheckCollision(Geometry* _otherGeometry)
{
	// Check Collision logic
	return false;
}

void ComplexGeometry::DoCollision(Geometry* _otherGeometry)
{
	// Do Collision logic
	cout << "No Do CollisionLogic for this object type\n";
}

void ComplexGeometry::drawVertexGeometry()
{
	if (ShouldRender)
	{
		if (ObjectShader)
		{
			ObjectShader->use();
			ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
		}

		Geometry::drawVertexGeometry();
	}
}

void ComplexGeometry::Move(vec3 movementDirection, float deltatime)
{
	Geometry::Move(movementDirection, deltatime);
}

void ComplexGeometry::SetShouldDraw(bool state)
{
	ShouldRender = state;
}

