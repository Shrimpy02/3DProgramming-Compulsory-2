#pragma once

// Class includes
#include "Shader.h"
#include "Camera.h"
#include "GameManager.h"
#include "Geometry.h"
#include "Game/Characters/PlayerCharacter.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h" // Image loader file


// ------------------- Global Variable`s ------------------- 
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

double deltaTime = 0.0;
double lastFrame = 0.0;

// Bool`s
bool firstMouse = true;

// Object`s
//Camera* myCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Game
GameManager* GameManagerObject = new GameManager(SCR_WIDTH, SCR_HEIGHT);

// ------------------- Function`s -------------------

// Calculations`s

inline void updateDeltaTime()
{
	// Calculate`s the delta time between each frame
	// for a smooth and constant user experience
	double currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

}

// Callback`s

inline void mouse_callback(GLFWwindow* window, double _xPos, double _yPos)
{
	float xpos = static_cast<float>(_xPos);
	float ypos = static_cast<float>(_yPos);

	// First move check makes sure camera does not jerk on first mouse movement
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	GameManagerObject->GetPlayer()->GetCamera()->ProcessMouseMovement(xoffset, yoffset);
}

inline void scroll_callback(GLFWwindow* window, double _xOffset, double _yOffset)
{
	GameManagerObject->GetPlayer()->GetCamera()->ProcessMouseScroll(static_cast<float>(_yOffset));
}

inline void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// Callback to glViewport called each frame for dynamic window re-sizing. 
	glViewport(0, 0, width, height);
}

// Initialization`s

inline void initializeCallbacks(GLFWwindow* _window)
{
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
}

inline GLFWwindow* initializeWindow(const char* _windowName)
{
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, _windowName, NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	initializeCallbacks(window);

	return window;
}

inline void GLFInitialization()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}