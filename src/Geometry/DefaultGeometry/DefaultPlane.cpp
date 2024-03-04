// Class includes
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

DefaultPlane::~DefaultPlane()
{
	Geometry::~Geometry();
}

void DefaultPlane::Initialize()
{
	Geometry::Initialize(&PlaneVertices, NumVariables);
}

void DefaultPlane::BeginPlayGeometry()
{
	Geometry::BeginPlayGeometry();
}

void DefaultPlane::TickVertexGeometry(float deltatime)
{
	Geometry::TickVertexGeometry(deltatime);
}

bool DefaultPlane::CheckCollision(Geometry* _otherGeometry)
{
	// Check Collision logic
	//cout << "No Do CollisionLogic for this object type\n";
	return false;
}

void DefaultPlane::DoCollision(Geometry* _otherGeometry)
{
	// Do Collision logic
	cout << "No Do CollisionLogic for this object type\n";
}

void DefaultPlane::drawVertexGeometry()
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

void DefaultPlane::Move(vec3 movementDirection, float deltatime)
{
	Geometry::Move(movementDirection, deltatime);
}

void DefaultPlane::SetShouldDraw(bool state)
{
	ShouldRender = state;
}

