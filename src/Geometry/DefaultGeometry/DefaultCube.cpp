#include "DefaultCube.h"

#include <iostream>

DefaultCube::DefaultCube()
{
}

void DefaultCube::Initialize()
{
	Geometry::Initialize(&CubeVertices, NumVariables);
}
