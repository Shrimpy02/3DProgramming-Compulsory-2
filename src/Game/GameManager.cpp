#include "GameManager.h"
#include "LevelManager.h"

GameManager::GameManager()
{
	LevelManagerObject = new LevelManager();
}

GameManager::~GameManager()
{
	LevelManagerObject->~LevelManager();
	delete LevelManagerObject;
}

void GameManager::BeginPlay()
{
	//std::cout << "GameManager::BeginPlay" << std::endl;
	LevelManagerObject->BeginPlay();
}

void GameManager::Tick(float deltatime)
{
	//std::cout << "GameManager::Tick" << std::endl;
	LevelManagerObject->TickDraw();
}