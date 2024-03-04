
#pragma once
#include "GameObject.h"
class Door : public GameObject
{
public:
	// ---------- Global Constants --------------


private:
	// ---------- Local Constants --------------

	bool doorShouldOpen = false;
	bool DoOnce = true;

	vec3 ClosedPosition = vec3(0, 0, 0);
	vec3 OpenPosition = vec3(0,0,0);

public:
	// ---------- Global functions --------------

	Door();

	Door(vec3 _worldPosition,
		vec3 _worldScale = vec3(1.f, 1.f, 1.f),
		float _worldRotationInDegrees = 0.f,
		vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

	~Door();

	void AttachGeometry(class DefaultCube* _renderBoxReference, class DefaultCube* _hitBoxReference) override;

	void BeginPlayObject() override;

	void TickObject(float deltatime) override;

	void ToggleDoor();

private:
	// ---------- Local functions --------------

	bool OpenDoor(float deltatime);

	bool CloseDoor(float deltatime);

public:
	// -------- Getters and setters ------------


};

