#pragma once
// Class includes
#include "Geometry.h"

// namespaces
using namespace std;
using namespace glm;

class DefaultSphere : public Geometry
{
public:
    // ---------- Global Constants --------------

    int NumSubDivides = 3;

private:
    // ---------- Local Constants --------------

    // Meta
    struct Vertex
    {
        float x, y, z, nx, ny, nz, r, g, b;
    };

    // Current Shader
    class Shader* ObjectShader = nullptr;

    // Meta
    const int NumVariables = 9;

    // Color
    const float r = 0.5f;
    const float g = 0.5f;
    const float b = 0.5f;

    vector<Vertex*> SphereVerticesStruct;

    vector<float> SphereVertices;

public:
    // ---------- Global functions --------------
    DefaultSphere();

    DefaultSphere(Shader* _shader,int _numSubDivides, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
        vec3 _worldScale = vec3(1.f, 1.f, 1.f),
        float _worldRotationInDegrees = 0.f,
        vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

    ~DefaultSphere();

    void Initialize() override;

    void BeginPlayGeometry() override;

    void TickVertexGeometry(float deltatime) override;

    bool CheckCollision(Geometry* _otherGeometry) override;

    void DoCollision(Geometry* _otherGeometry) override;

    void drawVertexGeometry() override;

    void Move(vec3 movementDirection, float deltatime) override;


private:
    // ---------- Local functions --------------

    void GenerateSphere(int NumSubDivides);

    void SubDivide(const vec3& a, const vec3& b, const vec3& c, int n);

    void MakeTriangle(const vec3& a, const vec3& b, const vec3& c);

    void makeSphere();

public:
    // ---------- Getters and setters --------------

    void SetShouldDraw(bool state) override;

};

