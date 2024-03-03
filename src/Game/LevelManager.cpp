#include "LevelManager.h"
#include "Geometry.h"
#include "Shader.h"
#include "Game/Characters/PlayerCharacter.h"
// Geometry
#include "DefaultGeometry/DefaultCube.h"
#include "DefaultGeometry/DefaultPlane.h"
#include "DefaultGeometry/DefaultPyramid.h"
#include "DefaultGeometry/DefaultSphere.h"
#include "DefaultGeometry/ComplexGeometry.h"
#include "GLFW/glfw3.h"

LevelManager::LevelManager()
{

}

LevelManager::LevelManager(class Camera* _camera, class PlayerCharacter* _player, unsigned int& _screenWidth, unsigned int& _screenHeight)
{
	PlayerCamera = _camera;
	Player = _player;
	ScreenWidth = _screenWidth;
	ScreenHeight = _screenHeight;
}

LevelManager::~LevelManager()
{
	// Deconstructs all level geometry
	for(auto* _geometry : GeometryInLevel)
	{
		DeleteGeometry(_geometry);
	}

	// Deconstructs Shaders
	DefaultShader->~Shader();
	LightShader->~Shader();
	NormalShader->~Shader();
}

void LevelManager::BeginPlay()
{
	// Shader objects constructed
	DefaultShader = new Shader("ShaderSourceCode/vertexShader.vs", "ShaderSourceCode/fragmentShader.fs", PlayerCamera, ScreenWidth, ScreenHeight);
	LightShader = new Shader("ShaderSourceCode/lightVertexShader.vs", "ShaderSourceCode/lightFragmentShader.fs", PlayerCamera, ScreenWidth, ScreenHeight);
	NormalShader = new Shader("ShaderSourceCode/normalVertexShader.vs", "ShaderSourceCode/normalFragmentShader.fs", PlayerCamera, ScreenWidth, ScreenHeight);

	// Construct and add geometry to level

	// Light:
	GeometryInLevel.push_back(new DefaultSphere(LightShader, vec3(0, 10, 0)));

	// World:
	GeometryInLevel.push_back(new DefaultPlane(DefaultShader, vec3(0, 0, -1), vec3(10, 1, 15)));

	// Collision test
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(1, 0, 2), vec3(0.4f, 0.4f, 0.4f)));
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(-1, 0.6, 2), vec3(0.4f, 0.4f, 0.4f)));

	// House:
	// walls
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(-2, 0.5, -4), vec3(3, 2, 0.5)));
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(2, 0.5, -4), vec3(3, 2, 0.5)));
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(-3.7, 0.5, -6.1), vec3(5, 2, 0.5),90,vec3(0,1,0)));
	GeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(3.7, 0.5, -6.1), vec3(5, 2, 0.5), 90, vec3(0, 1, 0)));
	// Ceiling
	GeometryInLevel.push_back(new DefaultPyramid(DefaultShader, vec3(0, 2.5, -6.1), vec3(8.2, 2, 6)));

	// Player:
	DefaultCube* playerHitbox = new DefaultCube(DefaultShader, vec3(0, 0, 0), vec3(0.4, 0.8, 0.4));
	

	// Initialize all level geometry
	for (auto* _geometry : GeometryInLevel)
	{
		InitializeGeometry(_geometry);
	}

	// Initialize player geometry
	Player->InitializeHitbox(playerHitbox);
	GeometryInLevel.push_back(playerHitbox);
}

void LevelManager::Tick(float deltatime)
{
	//for (auto* _geometry : GeometryInLevel)
	//{
	//	TickGeometry(_geometry);
	//}
	//GeometryInLevel[2]->Move(vec3(-2.0f, 0.0f, 0.0f), deltatime);
	//GeometryInLevel[3]->Move(vec3(2.0f, 0.0f, 0.0f), deltatime);
}

void LevelManager::TickDraw()
{
	LightShader->use();
	LightShader->setVec3("objectColor", vec3(1.0, 1.0, 1.0));
	LightShader->setVec3("lightColor", vec3(1.0, 1.0, 1.0));
	DefaultShader->use();
	DefaultShader->setVec3("lightColor", vec3(1.0, 1.0, 1.0));
	vec3 lightPos = vec3(0.0, 0.0, 0.0);
	vec3 viewPos = PlayerCamera->Position;
	DefaultShader->setVec3("lightPos", lightPos);
	DefaultShader->setVec3("viewPos", viewPos);

	for (auto* _geometry : GeometryInLevel)
	{
		DrawGeometry(_geometry);
	}

}

void LevelManager::CheckCollision()
{
	//size_t numGeometries = GeometryInLevel.size();

	//for (size_t i = 0; i < numGeometries; ++i)
	//{
	//	for (size_t j = i + 1; j < numGeometries; ++j)
	//	{
	//		if (GeometryInLevel[i]->CheckCollision(GeometryInLevel[j])) {
	//			// Collision detected! Handle it as needed.
	//			std::cout << "Collision between geometries " << i << " and " << j << std::endl;
	//			// Add collision response code here...
	//		}
	//	}
	//}

	if(erase)
	{
		if (GeometryInLevel[9]->CheckCollision(GeometryInLevel[3]))
		{
			GeometryInLevel[9]->DoCollision(GeometryInLevel[3]);
			GeometryInLevel.erase(remove(GeometryInLevel.begin(), GeometryInLevel.end(), GeometryInLevel[3]), GeometryInLevel.end());
			erase = false;
		}
	}

}

void LevelManager::AddObjectToLevel(Geometry* _geometryToAdd)
{
	GeometryInLevel.push_back(_geometryToAdd);
}

template <typename T>
void LevelManager::CollideGeometry(T* collider, T* collided)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		collider->DoCollision(collider, collided);
	}
}

template <typename T>
void LevelManager::TickGeometry(T* _geometry)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		_geometry->TickVertexGeometry();
	}
}

template<typename T>
void LevelManager::DrawGeometry(T* _geometry)
{
	if (_geometry->ShouldDraw() == true)
	{
		if constexpr (is_same_v<T, Geometry>)
		{
			_geometry->drawVertexGeometry();
		}
	}
}

template <typename T>
void LevelManager::DeleteGeometry(T* _geometry)
{
	if constexpr(is_same_v<T,Geometry>)
	{
		_geometry->~Geometry();
		delete _geometry;
	}

}

template <typename T>
void LevelManager::InitializeGeometry(T* _geometry)
{
	if constexpr(is_same_v<T, Geometry>) 
	{
		_geometry->Initialize();
	}
}

