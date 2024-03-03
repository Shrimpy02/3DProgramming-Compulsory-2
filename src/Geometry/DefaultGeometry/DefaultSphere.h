#pragma once
#include "Geometry.h"

using namespace std;


class DefaultSphere : public Geometry
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
    struct Vertex
    {
        float x, y, z, nx, ny, nz, r, g, b;
    };

    vector<Vertex*> SphereVerticesStruct;

    vector<float> SphereVertices;

    int NumSubDivides = 3;

    const int NumVariables = 9;

    // Colors
    const float r = 0.5f;
    const float g = 0.5f;
    const float b = 0.5f;

  

public:
    // ---------- Global functions --------------
    DefaultSphere();

    DefaultSphere(Shader* _shader, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
        vec3 _worldScale = vec3(1.f, 1.f, 1.f),
        float _worldRotationInDegrees = 0.f,
        vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));


    void Initialize() override;

    void drawVertexGeometry() override;

private:
    // ---------- Local functions --------------

    void SubDivide(const vec3& a, const vec3& b, const vec3& c, int n);

    void MakeTriangle(const vec3& a, const vec3& b, const vec3& c);

    void makeSphere();

    void TickVertexGeometry();

public:
    // ---------- Getters and setters --------------



};

