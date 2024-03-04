#pragma once
#include "glm/glm.hpp"

using namespace glm;

class PlayerCharacter
{
public:
	// ---------- Global Constants --------------

		// Camera Attributes
	vec3 Position;
	float Yaw;

	float MovementSpeed = 1.f;

	class DefaultCube* Hitbox = nullptr;

private:
	// ---------- Local Constants --------------
	float deltaTime;

	class Camera* PlayerCamera = nullptr;

	bool IsInteracting = false;

public:
	// ---------- Global functions --------------

	PlayerCharacter();

	PlayerCharacter(vec3 _position);

	~PlayerCharacter();

	void InitializeHitbox(class DefaultCube* _hitboxReference);

	void BeginPlay();

	void Tick(float deltatime);

	void ProcessInput(struct GLFWwindow* window);

private:
	// ---------- Local functions --------------

public:
	// -------- Getters and setters ------------

	Camera* GetCamera() { return PlayerCamera; }
	template <typename T>
	void SetHitbox(T* _hitbox) { Hitbox = _hitbox; }

	bool GetIsInteracting() { return IsInteracting; }
};

