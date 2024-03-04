#pragma once
#include "GameObject.h"
class Trophie : public GameObject
{
public:
	// ---------- Global Constants --------------


private:
	// ---------- Local Constants --------------

	float LevitateOffsetTime;

public:
	// ---------- Global functions --------------

	Trophie();

	Trophie(vec3 _worldPosition,
				vec3 _worldScale = vec3(1.f, 1.f, 1.f),
				float _worldRotationInDegrees = 0.f,
				vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

	~Trophie();

	void AttachGeometry(class DefaultCube* _renderBoxReference, class DefaultCube* _hitBoxReference) override;

	void BeginPlayObject() override;

	void TickObject(float deltatime) override;

private:
	// ---------- Local functions --------------

	void Levitate(float deltatime);

public:
	// -------- Getters and setters ------------


};

