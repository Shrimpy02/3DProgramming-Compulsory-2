#pragma once
// Class includes
#include "Geometry.h"

// namespaces
using namespace std;
using namespace glm;
class DefaultPyramid : public Geometry
{
public:
	// ---------- Global Constants --------------

private:
	// ---------- Local Constants --------------

    // Current Shader
    class Shader* ObjectShader = nullptr;

    // Meta
    const int NumVariables = 9;

    // Color
    const float r = 0.5f;
    const float g = 0.5f;
    const float b = 0.5f;

    vector<float> PyramidVertices = {
        // Base
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, r, g, b,

        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, r, g, b,

        // Front face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.707f, -0.707f, r, g, b,
        0.5f, -0.5f, -0.5f, 0.0f, 0.707f, -0.707f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.0f, 0.707f, -0.707f, r, g, b,

        // Right face
        0.5f, -0.5f, -0.5f, 0.707f, 0.707f, 0.0f, r, g, b,
        0.5f, -0.5f, 0.5f, 0.707f, 0.707f, 0.0f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.707f, 0.707f, 0.0f, r, g, b,

        // Back face
        0.5f, -0.5f, 0.5f, 0.0f, 0.707f, 0.707f, r, g, b,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.707f, 0.707f, r, g, b,
        0.0f, 0.5f, 0.0f, 0.0f, 0.707f, 0.707f, r, g, b,

        // Left face
        -0.5f, -0.5f, 0.5f, -0.707f, 0.707f, 0.0f, r, g, b,
        -0.5f, -0.5f, -0.5f, -0.707f, 0.707f, 0.0f, r, g, b,
        0.0f, 0.5f, 0.0f, -0.707f, 0.707f, 0.0f, r, g, b,
    };

public:
	// ---------- Global functions --------------
	DefaultPyramid();

    DefaultPyramid(Shader* _shader, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
        vec3 _worldScale = vec3(1.f, 1.f, 1.f),
        float _worldRotationInDegrees = 0.f,
        vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

    ~DefaultPyramid();

    void Initialize() override;

    void BeginPlayGeometry() override;

    void TickVertexGeometry(float deltatime) override;

    bool CheckCollision(Geometry* _otherGeometry) override;

    void DoCollision(Geometry* _otherGeometry) override;

    void drawVertexGeometry() override;

    void Move(vec3 movementDirection, float deltatime) override;


private:
	// ---------- Local functions --------------



public:
	// ---------- Getters and setters --------------

    void SetShouldDraw(bool state) override;


};

