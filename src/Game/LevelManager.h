#pragma once

// C++ specific components
#include <vector>
#include "iostream"

// Classes
#include "GameManager.h"

// Namespaces
using namespace std;

class Geometry;

class LevelManager
{
public:
	// ---------- Global Constants --------------

private:
	// ---------- Local Constants --------------
	vector<Geometry*> GeometryInLevel;

public:
	// ---------- Global functions --------------
	LevelManager();

	~LevelManager();

	void BeginPlay();

	void Tick(float deltatime);

	void TickDraw();

	void CheckCollision();

	void AddObjectToLevel(Geometry* _geometryToAdd);

	template <typename T>
	void DrawGeometry(T* _geometry);

private:
	// ---------- Local functions --------------
	template <typename T>
	void DeleteGeometry(T* _geometry);

	template <typename T>
	void InitializeGeometry(T* _geometry);

public:
	// ---------- Getters and setters --------------


};
