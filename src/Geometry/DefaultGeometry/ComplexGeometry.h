#pragma once
// Class includes
#include "Geometry.h"

// namespaces
using namespace std;
using namespace glm;
class ComplexGeometry : public Geometry
{
public:
    // ---------- Global Constants -------------

private:
    // ---------- Local Constants --------------

// Current Shader
    class Shader* ObjectShader = nullptr;

    // Meta
    const int NumVariables = 6; // This is outdated and should be gotten from function that reads file
    const char* FilePath;

    vector<float>* ComplexGeometryVertices;

public:
    // ---------- Global functions --------------
    ComplexGeometry();

    ComplexGeometry(const char* _filePath, Shader* _shader, vec3 _worldPosition = vec3(0.f, 0.f, 0.f),
        vec3 _worldScale = vec3(1.f, 1.f, 1.f),
        float _worldRotationInDegrees = 0.f,
        vec3 _worldRotationAxis = vec3(0.f, 0.f, 1.f));

    ~ComplexGeometry();

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

