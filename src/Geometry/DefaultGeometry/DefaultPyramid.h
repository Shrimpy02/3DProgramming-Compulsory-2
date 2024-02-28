#pragma once
#include "Geometry.h"

using namespace std;

class DefaultPyramid : public Geometry
{
public:
	// ---------- Global Constants --------------

private:
	// ---------- Local Constants --------------

	const int NumVariables = 9;

	// Colors
	const float r = 0.5f;
	const float g = 0.5f;
	const float b = 0.5f;

    vector<float> PyramidVertices = {
        // Base
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,

        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,

        // Front face
        -0.5f, -0.5f, -0.5f, 0.0f, -0.707f, 0.707f, r, g, b,
        0.5f, -0.5f, -0.5f, 0.0f, -0.707f, 0.707f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.0f, -0.707f, 0.707f, r, g, b,

        // Right face
        0.5f, -0.5f, -0.5f, -0.707f, -0.707f, 0.0f, r, g, b,
        0.5f, -0.5f, 0.5f, -0.707f, -0.707f, 0.0f, r, g, b,
        0.0f, 0.5f, 0.0f, -0.707f, -0.707f, 0.0f, r, g, b,

        // Back face
        0.5f, -0.5f, 0.5f, 0.0f, -0.707f, -0.707f, r, g, b,
        -0.5f, -0.5f, 0.5f, 0.0f, -0.707f, -0.707f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.0f, -0.707f, -0.707f, r, g, b,

        // Left face
        -0.5f, -0.5f, 0.5f, 0.707f, -0.707f, 0.0f, r, g, b,
        -0.5f, -0.5f, -0.5f, 0.707f, -0.707f, 0.0f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.707f, -0.707f, 0.0f, r, g, b,
    };

public:
	// ---------- Global functions --------------
	DefaultPyramid();

	void Initialize() override;

private:
	// ---------- Local functions --------------



public:
	// ---------- Getters and setters --------------



};

