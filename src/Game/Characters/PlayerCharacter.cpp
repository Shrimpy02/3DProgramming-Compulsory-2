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
	if(ControllsCamera)
	{
		PlayerCamera->Position = WorldPosition;
		WorldRotationInDegrees = -PlayerCamera->Yaw;
	}

	velocity = MovementSpeed * deltaTime;

	MovementDirection = PlayerCamera->Front * velocity;

	CanMoveZ = true;
	CanMoveX = true;

	Character::TickCharacter(deltatime);
}

void PlayerCharacter::ProcessInput(GLFWwindow* window)
{
	// GLFW input management
	// -------------------------

	// Usability
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float OringalY = WorldPosition.y;

	


	PlayerCamera->SetMovementMode(WALKING);
	if(ControllsCamera)
	{
		// Camera Movement
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && CanMoveZ)
			WorldPosition += MovementDirection;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && CanMoveZ)
			WorldPosition -= MovementDirection;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && CanMoveX)
			WorldPosition -= PlayerCamera->Right * velocity;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && CanMoveX)
			WorldPosition += PlayerCamera->Right * velocity;
	}
	else
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && CanMoveZ)
			WorldPosition += vec3(0, 0, -1) * velocity;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && CanMoveZ)
			WorldPosition -= vec3(0, 0, -1) * velocity;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && CanMoveX)
			WorldPosition -= vec3(1, 0, 0) * velocity;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && CanMoveX)
			WorldPosition += vec3(1, 0, 0) * velocity;
	}

		

		WorldPosition.y = OringalY;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && CanInteract)
	{
		CanInteract = false;
		IsInteracting = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
	{
		CanInteract = true;
		IsInteracting = false;
	}
	else 
		IsInteracting = false;

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && CanChangePath)
	{
		CanChangePath = false;
		NPCReference->ChangePath();
	}
	else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		CanChangePath = true;
	}

}
 