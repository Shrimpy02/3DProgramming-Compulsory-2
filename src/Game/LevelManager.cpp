#include "LevelManager.h"
#include "Geometry.h"
#include "DefaultGeometry/DefaultCube.h"
#include "DefaultGeometry/DefaultPlane.h"
#include "DefaultGeometry/DefaultPyramid.h"
#include "DefaultGeometry/DefaultSphere.h"

LevelManager::LevelManager()
{

	// Construct and add geometry to level
	GeometryInLevel.push_back(new DefaultSphere());
	//GeometryInLevel.push_back(new DefaultPyramid());
	//GeometryInLevel.push_back(new DefaultCube());
	GeometryInLevel.push_back(new DefaultPlane());
}

LevelManager::~LevelManager()
{
	// Deconstructs all level geometry
	for(auto* _geometry : GeometryInLevel)
	{
		DeleteGeometry(_geometry);
	}
}

void LevelManager::BeginPlay()
{

	// Initialize all level geometry
	for (auto* _geometry : GeometryInLevel)
	{
		InitializeGeometry(_geometry);
	}

}

void LevelManager::Tick(float deltatime)
{

}

void LevelManager::TickDraw()
{
	for (auto* _geometry : GeometryInLevel)
	{
		DrawGeometry(_geometry);
	}
}

void LevelManager::CheckCollision()
{
}

void LevelManager::AddObjectToLevel(Geometry* _geometryToAdd)
{
	GeometryInLevel.push_back(_geometryToAdd);
}

template<typename T>
void LevelManager::DrawGeometry(T* _geometry)
{
	if constexpr(is_same_v<T,Geometry>)
	{
		_geometry->drawVertexGeometry();
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

