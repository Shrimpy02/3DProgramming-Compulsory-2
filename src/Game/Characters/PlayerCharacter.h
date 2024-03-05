#pragma once

#include "Character.h"
#include "glm/glm.hpp"

using namespace glm;
class PlayerCharacter : public Character
{
public:
	// ---------- Global Constants --------------

	bool ControllsCamera = true;

	float velocity;

	float MovementSpeed = 2.f;

private:
	// ---------- Local Constants --------------
	float deltaTime;

	class Camera* PlayerCamera = nullptr;

	bool IsInteracting = false;

	bool CanChangePath = true;

	bool CanInteract = true;

	class NPC* NPCReference;

public:
	// ---------- Global functions --------------

	PlayerCharacter();

	PlayerCharacter(vec3 _worldPosition,
		vec3 _worldScale = vec3(1.f, 1.f, 1.f),
		float _worldRotationInDegrees = 0.f,
		vec3 _worldRotationAxis = vec3(0.f, 1.f, 0.f));

	~PlayerCharacter();

	void AttachGeometry(class DefaultCube* _renderBoxReference, class DefaultCube* _hitBoxReference) override;

	void BeginPlayCharacter() override;

	void TickCharacter(float deltatime) override;

	void ProcessInput(struct GLFWwindow* window);

private:
	// ---------- Local functions --------------

public:
	// -------- Getters and setters ------------

	Camera* GetCamera() { return PlayerCamera; }

	bool GetIsInteracting() { return IsInteracting; }

	void SetNPCReference(class NPC* _ref) { NPCReference = _ref; }
};

