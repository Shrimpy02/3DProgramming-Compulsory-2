#include "DefaultPyramid.h"

#include <iostream>
 
DefaultPyramid::DefaultPyramid()
{
}

void DefaultPyramid::Initialize()
{
	Geometry::Initialize(&PyramidVertices, NumVariables);
}
