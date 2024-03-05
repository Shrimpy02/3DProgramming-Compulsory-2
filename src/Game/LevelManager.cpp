#include "LevelManager.h"
#include "Geometry.h"
#include "Shader.h"
#include "Game/Characters/PlayerCharacter.h"
// Geometry


#include "Characters/NPC.h"
#include "DefaultGeometry/DefaultCube.h"
#include "DefaultGeometry/DefaultPlane.h"
#include "DefaultGeometry/DefaultPyramid.h"
#include "DefaultGeometry/DefaultSphere.h"
#include "DefaultGeometry/ComplexGeometry.h"
#include "GameObjects/Door.h"
#include "GameObjects/Trophie.h"
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
	for(auto* _geometry : StaticGeometryInLevel)
	{
		DeleteObject(_geometry);
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
	StaticGeometryInLevel.push_back(new DefaultSphere(LightShader, 3,vec3(0, 10, 0)));

	// World:
	StaticGeometryInLevel.push_back(new DefaultPlane(DefaultShader, vec3(0, 0, -1), vec3(15, 1, 15)));

	// House:
	// walls
	StaticGeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(-2, 0.5, -4), vec3(3, 2, 0.5)));
	StaticGeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(2, 0.5, -4), vec3(3, 2, 0.5)));
	StaticGeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(-3.7, 0.5, -6.1), vec3(5, 2, 0.5),90,vec3(0,1,0)));
	StaticGeometryInLevel.push_back(new DefaultCube(DefaultShader, vec3(3.7, 0.5, -6.1), vec3(5, 2, 0.5), 90, vec3(0, 1, 0)));
	// Ceiling
	StaticGeometryInLevel.push_back(new DefaultPyramid(DefaultShader, vec3(0, 2.5, -6.1), vec3(8.2, 2, 6)));

	// Construct and add game objects to level
	// Trophies
	GameObjectsInLevel.push_back(new Trophie(vec3(6, 0.6, 4), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(6, 0.6, 1), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(6, 0.6, -2), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(6, 0.6, -5), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(-6, 0.6, 4), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(-6, 0.6, 1), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(-6, 0.6, -2), vec3(0.4f, 0.4f, 0.4f)));
	GameObjectsInLevel.push_back(new Trophie(vec3(-6, 0.6, -5), vec3(0.4f, 0.4f, 0.4f)));

	// Doors
	GameObjectsInLevel.push_back(new Door(vec3(0, 0.5, -4), vec3(1, 2.2, 0.3)));

	// Initialize Characters in Level
	// Player
	CharactersInLevel.push_back(Player);

	//NPC
	class NPC* npc1 = new NPC(vec3(0, 0.6, 4));
	CharactersInLevel.push_back(npc1);
	Player->SetNPCReference(npc1);

	// Initialize all level geometry
	for (auto* _geometry : StaticGeometryInLevel)
	{
		InitializeGeometry(_geometry);
	}

	// Initialize all level gameobjects
	for (auto* _geometry : GameObjectsInLevel)
	{
		_geometry->AttachGeometry(new DefaultCube(DefaultShader), new DefaultCube(DefaultShader));
		InitializeGeometry(_geometry);
	}

	// Initialize all level characters
	for (auto* _geometry : CharactersInLevel)
	{
		_geometry->AttachGeometry(new DefaultCube(DefaultShader), new DefaultCube(DefaultShader));
		InitializeGeometry(_geometry);
	}

	// Runs begin play
	for (auto* _geometry : StaticGeometryInLevel)
	{
		BeginPlayGeometry(_geometry);
	}

	for (auto* _geometry : GameObjectsInLevel)
	{
		BeginPlayGeometry(_geometry);
	}

	for (auto* _geometry : CharactersInLevel)
	{
		BeginPlayGeometry(_geometry);
	}
}

void LevelManager::Tick(float deltatime)
{
	for (auto* _geometry : StaticGeometryInLevel)
	{
		TickGeometry(_geometry, deltatime);
	}
	for (auto* _geometry : GameObjectsInLevel)
	{
		TickGeometry(_geometry, deltatime);
	}
	for (auto* _geometry : CharactersInLevel)
	{
		TickGeometry(_geometry, deltatime);
	}
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

	for (auto* _geometry : StaticGeometryInLevel)
	{
		DrawGeometry(_geometry);
	}

	for (auto* _geometry : GameObjectsInLevel)
	{
		DrawGeometry(_geometry);
	}

	for (auto* _geometry : CharactersInLevel)
	{
		DrawGeometry(_geometry);
	}
}

void LevelManager::CheckCollision()
{
	for(auto* _GameObject : GameObjectsInLevel)
	{
		if (_GameObject->Hitbox->CheckCollision(Player->Hitbox))
		{
			// and player press button?
			DoCollision(_GameObject);
		}
	}

}

// PRIVATE -------------------------------

template <typename T>
void LevelManager::InitializeGeometry(T* _geometry)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		_geometry->Initialize();
	}
	else if constexpr (is_same_v<T, GameObject>)
	{
		_geometry->RenderBox->Initialize();
		_geometry->Hitbox->Initialize();
	}
	else if constexpr (is_same_v<T, Character>)
	{
		_geometry->RenderBox->Initialize();
		_geometry->Hitbox->Initialize();
	}
}

template <typename T>
void LevelManager::BeginPlayGeometry(T* _geometry)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		_geometry->BeginPlayGeometry();
	}
	else if constexpr (is_same_v<T, GameObject>)
	{
		_geometry->BeginPlayObject();
		_geometry->RenderBox->BeginPlayGeometry();
		_geometry->Hitbox->BeginPlayGeometry();
	}
	else if constexpr (is_same_v<T, Character>)
	{
		_geometry->BeginPlayCharacter();
		_geometry->RenderBox->BeginPlayGeometry();
		_geometry->Hitbox->BeginPlayGeometry();
	}
}

template <typename T>
void LevelManager::TickGeometry(T* _geometry,float deltatime)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		_geometry->TickVertexGeometry(deltatime);
	}
	else if constexpr (is_same_v<T, GameObject>)
	{
		_geometry->TickObject(deltatime);
		_geometry->RenderBox->TickVertexGeometry(deltatime);
		_geometry->Hitbox->TickVertexGeometry(deltatime);
	}
	else if constexpr (is_same_v<T, Character>)
	{
		_geometry->TickCharacter(deltatime);
		_geometry->RenderBox->TickVertexGeometry(deltatime);
		_geometry->Hitbox->TickVertexGeometry(deltatime);
	}
}

template<typename T>
void LevelManager::DrawGeometry(T* _geometry)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		_geometry->drawVertexGeometry();
	}
	else if constexpr (is_same_v<T, GameObject>)
	{
		_geometry->RenderBox->drawVertexGeometry();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		_geometry->Hitbox->drawVertexGeometry();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else if constexpr (is_same_v<T, Character>)
	{
		_geometry->RenderBox->drawVertexGeometry();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		_geometry->Hitbox->drawVertexGeometry();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

template <typename T>
void LevelManager::DoCollision(T* _geometry)
{
	if constexpr (is_same_v<T, Geometry>)
	{
		// Temp: Do nothing when player collides with geometry
	}
	else if constexpr (is_same_v<T, GameObject>)
	{
		if (dynamic_cast<Trophie*>(_geometry))
		{
			DeleteObject(_geometry);
		}
		else if (auto* door = dynamic_cast<Door*>(_geometry))
		{
			if(Player->GetIsInteracting())
			{
				door->ToggleDoor();
			}
		}
	}
}

template <typename T>
void LevelManager::DeleteObject(T* _geometry)
{
	if constexpr(is_same_v<T,Geometry>)
	{
		// Remove object fromm level static geometry vector
		auto _ElementToRemove = std::find(StaticGeometryInLevel.begin(), StaticGeometryInLevel.end(), _geometry);
		if (_ElementToRemove != StaticGeometryInLevel.end())
			StaticGeometryInLevel.erase(_ElementToRemove);

		_geometry->~Geometry(); // its being wierd...
		//delete _geometry;
	}

	else if constexpr (is_same_v<T, GameObject>)
	{
		// Remove object fromm level object vector
		auto _ElementToRemove = std::find(GameObjectsInLevel.begin(), GameObjectsInLevel.end(), _geometry);
		if (_ElementToRemove != GameObjectsInLevel.end()) 
			GameObjectsInLevel.erase(_ElementToRemove);
		
		_geometry->RenderBox->~DefaultCube();
		_geometry->Hitbox->~DefaultCube();

		_geometry->~GameObject();
		delete _geometry;
	}

	else if constexpr (is_same_v<T, Character>)
	{
		// Remove object fromm level object vector
		auto _ElementToRemove = std::find(CharactersInLevel.begin(), CharactersInLevel.end(), _geometry);
		if (_ElementToRemove != CharactersInLevel.end())
			CharactersInLevel.erase(_ElementToRemove);

		_geometry->RenderBox->~DefaultCube();
		_geometry->Hitbox->~DefaultCube();

		_geometry->~Character();
		delete _geometry;
	}
}


