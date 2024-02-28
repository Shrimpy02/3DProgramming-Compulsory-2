#include "DefaultPlane.h"

#include <iostream>

DefaultPlane::DefaultPlane()
{
}

void DefaultPlane::Initialize()
{
	Geometry::Initialize(&PlaneVertices, NumVariables);
}
