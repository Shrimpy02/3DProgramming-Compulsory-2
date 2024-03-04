#include "PlayerCharacter.h"

#include "Camera.h"
#include "Geometry.h"
#include "DefaultGeometry/DefaultCube.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

using namespace glm;

PlayerCharacter::PlayerCharacter()
{
	PlayerCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

PlayerCharacter::PlayerCharacter(vec3 _position)
{
	Position = _position;
	PlayerCamera = new Camera(_position);
	Hitbox = new DefaultCube();
}

PlayerCharacter::~PlayerCharacter()
{
	PlayerCamera->~Camera();
	if(Hitbox)
	{
		//Hitbox->~Geometry();
	}
}

void PlayerCharacter::InitializeHitbox(class DefaultCube* _hitboxReference)
{
	Hitbox = _hitboxReference;
	Hitbox->Initialize();
	Hitbox->ShouldRender = false;
}

void PlayerCharacter::BeginPlay()
{
	
}

void PlayerCharacter::Tick(float deltatime)
{
	deltaTime = deltatime;
	Position = PlayerCamera->Position;
	Yaw = -PlayerCamera->Yaw;

	if(Hitbox)
	{
		Hitbox->WorldPosition = Position + vec3(0,-0.2, 0);
		Hitbox->WorldRotationAxis = vec3(0.0f,1.0f,0.0f);
		Hitbox->WorldRotationInDegrees = Yaw;
	}
	
}

void PlayerCharacter::ProcessInput(GLFWwindow* window)
{
	// GLFW input management
	// -------------------------

	// Usability
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera Movement
		PlayerCamera->SetMovementMode(WALKING);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		PlayerCamera->ProcessKeyboard(DOWN, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		IsInteracting = true;
	else
		IsInteracting = false;

}
 