// Class includes
#include "DefaultCube.h"
#include "shader.h"

DefaultCube::DefaultCube()
{
}

DefaultCube::DefaultCube(Shader* _shader, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

DefaultCube::~DefaultCube()
{
	Geometry::~Geometry();
}

void DefaultCube::Initialize()
{
	Geometry::Initialize(&CubeVertices, NumVariables);
}

void DefaultCube::BeginPlayGeometry()
{
	Geometry::BeginPlayGeometry();
}

void DefaultCube::TickVertexGeometry(float deltatime)
{
	Geometry::TickVertexGeometry(deltatime);
}

bool DefaultCube::CheckCollision(Geometry* _otherGeometry)
{
	// for now there can only be collisions with default cubes.
	const DefaultCube* otherObject = dynamic_cast<const DefaultCube*>(_otherGeometry);

	// Calculate half scales
	float halfScaleX = WorldScale.x / 2.0f;
	float halfScaleY = WorldScale.y / 2.0f;
	float halfScaleZ = WorldScale.z / 2.0f;

	// Calculate half scales for the other cube
	float otherHalfScaleX = otherObject->WorldScale.x / 2.0f;
	float otherHalfScaleY = otherObject->WorldScale.y / 2.0f;
	float otherHalfScaleZ = otherObject->WorldScale.z / 2.0f;

	// Check for overlap along each axis
	bool overlapX = std::abs(WorldPosition.x - otherObject->WorldPosition.x) < halfScaleX + otherHalfScaleX;
	bool overlapY = std::abs(WorldPosition.y - otherObject->WorldPosition.y) < halfScaleY + otherHalfScaleY;
	bool overlapZ = std::abs(WorldPosition.z - otherObject->WorldPosition.z) < halfScaleZ + otherHalfScaleZ;

	// Return true if there is overlap along all three axes
	return overlapX && overlapY && overlapZ;

}

void DefaultCube::DoCollision(Geometry* _otherGeometry)
{

	// for now there can only be collisions with default cubes.
	const DefaultCube* otherObject = dynamic_cast<const DefaultCube*>(_otherGeometry);

	// temp delete collided with object
	otherObject->~DefaultCube();
	delete(otherObject);

	// temp text
	cout << "You got a trophie!" << endl;

}

void DefaultCube::drawVertexGeometry()
{
	if(ShouldRender)
	{
		if (ObjectShader)
		{
			ObjectShader->use();
			ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
		}

		Geometry::drawVertexGeometry();
	}
}

void DefaultCube::Move(vec3 movementDirection, float deltatime)
{
	Geometry::Move(movementDirection, deltatime);
}

void DefaultCube::SetShouldDraw(bool state)
{
	ShouldRender = state;
}

