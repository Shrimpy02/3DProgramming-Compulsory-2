// Class includes
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

DefaultPyramid::~DefaultPyramid()
{
	Geometry::~Geometry();
}


void DefaultPyramid::Initialize()
{
	Geometry::Initialize(&PyramidVertices, NumVariables);
}

void DefaultPyramid::BeginPlayGeometry()
{
	Geometry::BeginPlayGeometry();
}

void DefaultPyramid::TickVertexGeometry(float deltatime)
{
	Geometry::TickVertexGeometry(deltatime);
}

bool DefaultPyramid::CheckCollision(Geometry* _otherGeometry)
{
	// Check Collision logic
	return false;
}

void DefaultPyramid::DoCollision(Geometry* _otherGeometry)
{
	// Do Collision logic
	cout << "No Do CollisionLogic for this object type\n";
}

void DefaultPyramid::drawVertexGeometry()
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

void DefaultPyramid::Move(vec3 movementDirection, float deltatime)
{
	Geometry::Move(movementDirection, deltatime);
}

void DefaultPyramid::SetShouldDraw(bool state)
{
	ShouldRender = state;
}

