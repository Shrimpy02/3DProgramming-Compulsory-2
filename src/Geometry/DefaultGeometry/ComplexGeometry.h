#pragma once
#include "Geometry.h"

using namespace std;

class ComplexGeometry : public Geometry
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
    const char* FilePath;

	const int NumVariables = 6;

    vector<float>* ComplexGeometryVertices;

public:
    // ---------- Global functions --------------
    ComplexGeometry();

    ComplexGeometry(const char* _filePath, Shader* _shader, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
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

