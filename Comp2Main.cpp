
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

	// big change!

	// Shaders
	Shader myShader("ShaderSourceCode/vertexShader.vs", "ShaderSourceCode/fragmentShader.fs", &myCamera, SCR_WIDTH, SCR_HEIGHT);
	Shader lightShader("ShaderSourceCode/lightVertexShader.vs", "ShaderSourceCode/lightFragmentShader.fs", &myCamera, SCR_WIDTH, SCR_HEIGHT);
	Shader normalShader("ShaderSourceCode/normalVertexShader.vs", "ShaderSourceCode/normalFragmentShader.fs", &myCamera, SCR_WIDTH, SCR_HEIGHT);

	// Camera
	myCamera.SetMovementMode(FLYING);

	// Geometry
	// vector<float> defaultCubeVertices = {
	//	// positions		// normals	    	// Colors
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,0.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,0.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,1.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,0.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,0.0f,

	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,0.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 1.0f, 1.0f,1.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f,0.0f,

	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
	//	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,
	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,

	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,1.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f,

	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,0.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,0.0f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,0.0f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,0.0f,

	//	 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,0.0f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,0.0f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0.0f
	//};
	//vector<float> defaultCubeVerticesSolidColor = {
	//	// positions		// normals	    	// Colors
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.6f, 0.4f,0.2f,

	//	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.5f, 0.6f, 0.4f,0.2f,

	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,

	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.6f, 0.4f,0.2f,

	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.6f, 0.4f,0.2f,

	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f, 0.4f,0.2f,
	//};
	//vector<float> defaultCubeVerticesNoColor = {
	//		-0.5f, -0.5f, -0.5f,
	//		0.5f, -0.5f, -0.5f,
	//		0.5f, 0.5f, -0.5f,
	//		0.5f, 0.5f, -0.5f,
	//		-0.5f, 0.5f, -0.5f,
	//		-0.5f, -0.5f, -0.5f,

	//		-0.5f, -0.5f, 0.5f,
	//		0.5f, -0.5f, 0.5f,
	//		0.5f, 0.5f, 0.5f,
	//		0.5f, 0.5f, 0.5f,
	//		-0.5f, 0.5f, 0.5f,
	//		-0.5f, -0.5f, 0.5f,

	//		-0.5f, 0.5f, 0.5f,
	//		-0.5f, 0.5f, -0.5f,
	//		-0.5f, -0.5f, -0.5f,
	//		-0.5f, -0.5f, -0.5f,
	//		-0.5f, -0.5f, 0.5f,
	//		-0.5f, 0.5f, 0.5f,

	//		0.5f, 0.5f, 0.5f,
	//		0.5f, 0.5f, -0.5f,
	//		0.5f, -0.5f, -0.5f,
	//		0.5f, -0.5f, -0.5f,
	//		0.5f, -0.5f, 0.5f,
	//		0.5f, 0.5f, 0.5f,

	//		-0.5f, -0.5f, -0.5f,
	//		0.5f, -0.5f, -0.5f,
	//		0.5f, -0.5f, 0.5f,
	//		0.5f, -0.5f, 0.5f,
	//		-0.5f, -0.5f, 0.5f,
	//		-0.5f, -0.5f, -0.5f,

	//		-0.5f, 0.5f, -0.5f,
	//		0.5f, 0.5f, -0.5f,
	//		0.5f, 0.5f, 0.5f,
	//		0.5f, 0.5f, 0.5f,
	//		-0.5f, 0.5f, 0.5f,
	//		-0.5f, 0.5f, -0.5f
	//};
	//defaultGeometry.Initialize(&defaultCubeVertices, 9);
	//solidColorGeometry.Initialize(&defaultCubeVerticesSolidColor, 9);
	//lightGeometry.Initialize(&defaultCubeVerticesNoColor, 3);
	//testPlane.Initialize(testPlane.generateVertexGeometryFromFile("2_8_13ResultVert.txt"), 9);
	//testNormals.Initialize(testNormals.generateNormalGeometryFromFile("2_8_13ResultNorm.txt"), 6);

	if(firstTick == false)
	{
		GameManagerObject.BeginPlay();
		firstTick = true;
	}

	// ------------------- Render loop ------------------- 
	while (!glfwWindowShouldClose(window))
	{
		// ---------- Input ----------
		updateDeltaTime();

		// ProcessInput
		processInput(window);

		// ---------- Rendering options ----------
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ---------- Drawing ----------
		lightShader.use();
		lightShader.setVec3("objectColor", vec3(1.0, 1.0, 1.0));
		lightShader.setVec3("lightColor", vec3(1.0, 1.0, 1.0));
		myShader.use();
		myShader.setVec3("lightColor", vec3(1.0, 1.0, 1.0));
		vec3 lightPos = vec3(0.0, 0.0, 0.0);
		vec3 viewPos = myCamera.Position;
		myShader.setVec3("lightPos", lightPos);
		myShader.setVec3("viewPos", viewPos);
		myShader.processTransformations();

		// Rendering
		//float time = glfwGetTime();
		//defaultGeometry.drawVertexGeometry(false, &myShader, vec3(-1.0, 0.0, 0.0), vec3(0.3, 0.3, 0.3));
		//solidColorGeometry.drawVertexGeometry(false, &myShader, vec3(1.0, 0.0, 0.0), vec3(0.3, 0.3, 0.3), 45, vec3(0.0, 1.0, 0.0));
		//lightGeometry.drawVertexGeometry(false, &lightShader, lightPos, vec3(0.3, 0.3, 0.3));
		//testPlane.drawVertexGeometry(false, &myShader, vec3(0.0, 0.0, -3.0), vec3(0.2, 0.2, 0.2), time * 10, vec3(0.0, 1.0, 0.0));
		//testNormals.drawNormalGeometry(&normalShader, vec3(0.0, 0.0, -3.0), vec3(0.2, 0.2, 0.2), time * 10, vec3(0.0, 1.0, 0.0));

		// Game
		GameManagerObject.Tick(deltaTime);

		// GLFW: swap buffers and process events
		// -------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	defaultGeometry.~Geometry();
	lightGeometry.~Geometry();
	solidColorGeometry.~Geometry();
	//testPlane.~Geometry();
	//testNormals.~Geometry();

	glfwTerminate();
	return 0;
}
