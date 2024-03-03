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

	class PlayerCharacter* Player;

public:
	// ---------- Global functions --------------
	GameManager();

	GameManager(unsigned int& _screenWidth, unsigned int& _screenHeight);

	virtual ~GameManager();

	virtual void BeginPlay();

	virtual void Tick(float deltatime);

	void InputCalls(struct GLFWwindow* window);

private:
	// ---------- Local functions --------------



	
public:
	// ---------- Getters and setters --------------
	PlayerCharacter* GetPlayer() { return Player; }
};