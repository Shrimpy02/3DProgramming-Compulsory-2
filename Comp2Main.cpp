
// GL Components
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ specific components
#include "iostream"

// Class includes
#include "Main.h"

int main()
{
	// ------------------- Initialization ------------------- 
	// GLFW
	GLFInitialization();

	// Window
	GLFWwindow* window = initializeWindow("MainScreen");
	if (!window) return -1;

	// GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Faild to initialize GLAD" << std::endl;
		return -1;
	}

	// Camera
	//myCamera->SetMovementMode(WALKING);

	// Game
	GameManagerObject->BeginPlay();


	// ------------------- Render loop ------------------- 
	while (!glfwWindowShouldClose(window))
	{
		// ---------- Input ----------
		updateDeltaTime();

		// ProcessInput

		GameManagerObject->InputCalls(window);
		//processInput(window);

		// ---------- Rendering options ----------
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- Drawing ----------

		// Game
		GameManagerObject->Tick(deltaTime);

		// GLFW: swap buffers and process events
		// -------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	GameManagerObject->~GameManager();
	//myCamera->~Camera();

	glfwTerminate();
	return 0;
}
