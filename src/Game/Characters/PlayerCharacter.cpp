#include "PlayerCharacter.h"

#include "Camera.h"
#include "Geometry.h"
#include "NPC.h"
#include "DefaultGeometry/DefaultCube.h"
#include "GLFW/glfw3.h"
#include "glm/vec3.hpp"

using namespace glm;

PlayerCharacter::PlayerCharacter()
{
	PlayerCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

PlayerCharacter::PlayerCharacter(vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
	PlayerCamera = new Camera(_worldPosition);
}

PlayerCharacter::~PlayerCharacter()
{
	PlayerCamera->~Camera();
	if(Hitbox)
	{
		//Hitbox->~Geometry();
	}
}

void PlayerCharacter::AttachGeometry(DefaultCube* _renderBoxReference, DefaultCube* _hitBoxReference)
{
	Character::AttachGeometry(_renderBoxReference, _hitBoxReference);
	RenderBox->SetShouldDraw(false);
}

void PlayerCharacter::BeginPlayCharacter()
{
	Character::BeginPlayCharacter();
}

void PlayerCharacter::TickCharacter(float deltatime)
{
	deltaTime = deltatime;
	WorldPosition = PlayerCamera->Position;
	WorldRotationInDegrees = -PlayerCamera->Yaw;

	Character::TickCharacter(deltatime);
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

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && CanChangePath)
	{
		CanChangePath = false;
		NPCReference->ChangePath();
	}
	if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		CanChangePath = true;
	}

}
 