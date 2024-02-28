#pragma once
#include "Geometry.h"

using namespace std;


class DefaultSphere : public Geometry
{
public:
    // ---------- Global Constants --------------

private:
    // ---------- Local Constants --------------

    struct Vertex
    {
        float x, y, z, nx, ny, nz, r, g, b;
    };

    vector<Vertex*> SphereVerticesStruct;

    vector<float> SphereVertices;

    int NumSubDivides = 2;

    const int NumVariables = 9;

    // Colors
    const float r = 0.5f;
    const float g = 0.5f;
    const float b = 0.5f;

  

public:
    // ---------- Global functions --------------
    DefaultSphere();

    void Initialize() override;

private:
    // ---------- Local functions --------------

    void SubDivide(const vec3& a, const vec3& b, const vec3& c, int n);

    void MakeTriangle(const vec3& a, const vec3& b, const vec3& c);

    void makeSphere();

public:
    // ---------- Getters and setters --------------



};

