#pragma once
#include "Character.h"
#include <vector>

enum PathType
{
	Aproximate,
	Interpolated
};

class NPC :
    public Character
{
public:
	// ---------- Global Constants --------------

	float MovementSpeed = 2.f;
	std::vector<vec3> Path;

private:
	// ---------- Local Constants --------------
	int PathIt = 0;

	vec3 MovementVector;
	vec3 GoalPoint;

	PathType CurrentPathType = Aproximate;

public:
	// ---------- Global functions --------------

	NPC();

	NPC(vec3 _worldPosition,
		vec3 _worldScale = vec3(1.f, 1.f, 1.f),
		float _worldRotationInDegrees = 0.f,
		vec3 _worldRotationAxis = vec3(0.f, 1.f, 0.f));

	~NPC();

	void AttachGeometry(class DefaultCube* _renderBoxReference, class DefaultCube* _hitBoxReference) override;

	void BeginPlayCharacter() override;

	void TickCharacter(float deltatime) override;

	void ChangePath();

private:
	// ---------- Local functions --------------

	std::vector<vec3> ReadAproximatePath(const char* _filePath);

	std::vector<vec3> ReadInterpolatedPath(const char* _filePath);

	void MoveAlongPath(float deltatime);

	bool MoveToPoint(float deltatime);



public:
	// -------- Getters and setters ------------

};

