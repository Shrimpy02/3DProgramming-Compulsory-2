#pragma once

// C++ specific components
#include "iostream"

// Namespaces
using namespace std;

class GameManager
{
public:
	// ---------- Global Constants --------------

private:

	// ---------- Local Constants --------------
	class LevelManager* LevelManagerObject;
		
public:
	// ---------- Global functions --------------
	GameManager();

	virtual ~GameManager();

	virtual void BeginPlay();

	virtual void Tick(float deltatime);


private:
	// ---------- Local functions --------------



	
public:
	// ---------- Getters and setters --------------


};