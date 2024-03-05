#include "Character.h"
#include "DefaultGeometry/DefaultCube.h"

Character::Character()
{
}

Character::Character(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

Character::~Character()
{
}

void Character::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{
	RenderBox = _renderBoxReference;
	Hitbox = _hitBoxReference;
}

void Character::BeginPlayCharacter()
{
}

void Character::TickCharacter(float deltatime)
{
	if (!RenderBox) return;
	RenderBox->WorldPosition = WorldPosition - vec3(0, 0.5,0);
	RenderBox->WorldScale = WorldScale * vec3(1, 2, 1);
	RenderBox->WorldRotationInDegrees = WorldRotationInDegrees;
	RenderBox->WorldRotationAxis = WorldRotationAxis;

	if (!Hitbox) return;
	Hitbox->WorldPosition = WorldPosition - vec3(0, 0.5, 0);
	Hitbox->WorldScale = WorldScale*vec3(1.5,2,1.5);
	Hitbox->WorldRotationInDegrees = WorldRotationInDegrees;
	Hitbox->WorldRotationAxis = WorldRotationAxis;
}
