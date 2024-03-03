#pragma once
#include "Geometry.h"

using namespace std;

class DefaultPlane : public Geometry
{
public:
    // ---------- Global Constants --------------

private:
    // ---------- Local Constants --------------

	// World Transform
    Shader* ObjectShader = nullptr;

    vec3 WorldPosition;
    vec3 WorldScale;
    float WorldRotationInDegrees;
    vec3 WorldRotationAxis;

    // Meta
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

    DefaultPlane(Shader* _shader, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
				  vec3 _worldScale = vec3(1.f, 1.f, 1.f),
				  float _worldRotationInDegrees = 0.f,
				 vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));


    void Initialize() override;

    void drawVertexGeometry() override;

	void TickVertexGeometry();

private:
    // ---------- Local functions --------------



public:
    // ---------- Getters and setters --------------



};

