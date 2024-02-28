#pragma once
#include "Geometry.h"

using namespace std;

class DefaultPlane : public Geometry
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

    vector<float> PlaneVertices = {
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,

    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
    };

public:
    // ---------- Global functions --------------
    DefaultPlane();

    void Initialize() override;

private:
    // ---------- Local functions --------------



public:
    // ---------- Getters and setters --------------



};

