#include "GameManager.h"
#include "LevelManager.h"
#include "Characters/PlayerCharacter.h"
#include "glm/vec3.hpp"
#include "Camera.h"

GameManager::GameManager()
{
	Player = new PlayerCharacter();
	LevelManagerObject = new LevelManager();
}

GameManager::GameManager(unsigned int& _screenWidth, unsigned int& _screenHeight)
{
	Player = new PlayerCharacter(vec3(0.0f, 0.8f, 0.0f));
	LevelManagerObject = new LevelManager(Player->GetCamera(), Player, _screenWidth, _screenHeight);
}

GameManager::~GameManager()
{
	LevelManagerObject->~LevelManager();
	Player->~PlayerCharacter();
	delete LevelManagerObject;
}

void GameManager::BeginPlay()
{
	Player->BeginPlay();
	LevelManagerObject->BeginPlay();

}

void GameManager::Tick(float deltatime)
{
	Player->Tick(deltatime);
	LevelManagerObject->Tick(deltatime);
	LevelManagerObject->TickDraw();
	LevelManagerObject->CheckCollision();
}

void GameManager::InputCalls(GLFWwindow* window)
{
	Player->ProcessInput(window);
}
