#include "GameObject.h"

#include "DefaultGeometry/DefaultCube.h"

GameObject::GameObject()
{
}

GameObject::GameObject(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

GameObject::~GameObject()
{
}

void GameObject::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{
	RenderBox = _renderBoxReference;
	Hitbox = _hitBoxReference;
	//Hitbox->SetShouldDraw(false);
}

void GameObject::BeginPlayObject()
{
	if (!Hitbox) return;
	Hitbox->WorldPosition = WorldPosition;
	Hitbox->WorldScale = WorldScale * vec3(1.5, 1.5, 1.5);
	Hitbox->WorldRotationInDegrees = WorldRotationInDegrees;
	Hitbox->WorldRotationAxis = WorldRotationAxis;
}

void GameObject::TickObject(float deltatime)
{
	if (!RenderBox) return;
	RenderBox->WorldPosition = WorldPosition;
	RenderBox->WorldScale = WorldScale;
	RenderBox->WorldRotationInDegrees = WorldRotationInDegrees;
	RenderBox->WorldRotationAxis = WorldRotationAxis;

	//if (!Hitbox) return;
	//Hitbox->WorldPosition = WorldPosition;
	//Hitbox->WorldScale = WorldScale*vec3(1.5,1.5,1.5);
	//Hitbox->WorldRotationInDegrees = WorldRotationInDegrees;
	//Hitbox->WorldRotationAxis = WorldRotationAxis;
}
