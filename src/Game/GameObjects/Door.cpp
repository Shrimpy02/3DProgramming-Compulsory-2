#include "Door.h"
#include "GameObjects/Trophie.h"

Door::Door()
{
}

Door::Door(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	ClosedPosition = _worldPosition;
	OpenPosition = _worldPosition + vec3(1.0f, 0.0f, 0.0f);
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

Door::~Door()
{
	GameObject::~GameObject();
}

void Door::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{
	GameObject::AttachGeometry(_renderBoxReference, _hitBoxReference);
}

void Door::BeginPlayObject()
{
	GameObject::BeginPlayObject();
}

void Door::TickObject(float deltatime)
{
	GameObject::TickObject(deltatime);

	if(!DoOnce)
	{
		if (doorShouldOpen && OpenDoor(deltatime))
			DoOnce = true;

		else if (!doorShouldOpen && CloseDoor(deltatime))
			DoOnce = true;
	}
}

void Door::ToggleDoor()
{
	if(DoOnce)
	{

		if (doorShouldOpen)
			doorShouldOpen = false;
		else 
			doorShouldOpen = true;

		DoOnce = false;
	}
}

bool Door::OpenDoor(float deltatime)
{
	WorldPosition.x += OpenPosition.x * deltatime;

	if (WorldPosition.x >= OpenPosition.x) return true;

	return false;
}

bool Door::CloseDoor(float deltatime)
{
	WorldPosition.x -= OpenPosition.x * deltatime;

	if (WorldPosition.x <= ClosedPosition.x) return true;

	return false;
}
