#include "GameObjects/Trophie.h"

#include "GLFW/glfw3.h"
#include <algorithm>
Trophie::Trophie()
{
}

Trophie::Trophie(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

void Trophie::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{

	GameObject::AttachGeometry(_renderBoxReference, _hitBoxReference);
}

void Trophie::BeginPlayObject()
{
	LevitateOffsetTime = 1 + (rand() % 2);

	GameObject::BeginPlayObject();
}

void Trophie::TickObject(float deltatime)
{
	GameObject::TickObject(deltatime);
	Levitate(deltatime);
}

void Trophie::Levitate(float deltatime)
{
	
	WorldPosition.y = (LevitateOffsetTime + sin(glfwGetTime())) / 6;
}
