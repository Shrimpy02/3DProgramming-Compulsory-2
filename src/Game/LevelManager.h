#pragma once

// C++ specific components
#include <vector>

// Classes
#include "GameManager.h"

// Namespaces
using namespace std;

class LevelManager
{
public:
	// ---------- Global Constants --------------

private:
	// ---------- Local Constants --------------
	
	vector<class Geometry*> StaticGeometryInLevel;

	vector<class GameObject*> GameObjectsInLevel;

	class Camera* PlayerCamera;
	class PlayerCharacter* Player;
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;

	class Shader* DefaultShader;
	class Shader* LightShader;
	class Shader* NormalShader;

public:
	// ---------- Global functions --------------
	LevelManager();

	LevelManager(class Camera* _camera, class PlayerCharacter* _player, unsigned int& _screenWidth, unsigned int& _screenHeight);

	~LevelManager();

	void BeginPlay();

	void Tick(float deltatime);

	void TickDraw();

	void CheckCollision();

private:
	// ---------- Local functions --------------

	template <typename T>
	void InitializeGeometry(T* _geometry);

	template <typename T>
	void BeginPlayGeometry(T* _geometry);

	template <typename T>
	void TickGeometry(T* _geometry, float deltatime);

	template <typename T>
	void DrawGeometry(T* _geometry);

	template <typename T>
	void DoCollision(T* _geometry);

	template <typename T>
	void DeleteObject(T* _geometry);



public:
	// ---------- Getters and setters --------------


};
