#pragma once
#include "glm/vec3.hpp"

using namespace glm;
class Character
{
public:
	// ---------- Global Constants --------------

	// World data
	vec3 WorldPosition;
	vec3 WorldScale;
	float WorldRotationInDegrees;
	vec3 WorldRotationAxis;

	class DefaultCube* RenderBox = nullptr;

	class DefaultCube* Hitbox = nullptr;

private:
	// ---------- Local Constants --------------

public:
	// ---------- Global functions --------------

	Character();

	Character(vec3 _worldPosition,
				vec3 _worldScale = vec3(1.f, 1.f, 1.f),
				float _worldRotationInDegrees = 0.f,
				vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

	~Character();

	virtual void AttachGeometry(class DefaultCube* _renderBoxReference, class DefaultCube* _hitBoxReference);

	virtual void BeginPlayCharacter();

	virtual void TickCharacter(float deltatime);

private:
	// ---------- Local functions --------------

public:
	// -------- Getters and setters ------------

};

