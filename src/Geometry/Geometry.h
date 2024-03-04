#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

// Class includes
#include "glm/vec3.hpp"
#include <glad/glad.h>

// C++ includes
#include <vector>
#include <algorithm>
#include <iostream>
#include <iostream>

// structs
struct Vertex
{
	float x, y, z; // Position
	float nx, ny, nz; // normal vector
	float r, g, b; // Color
};

struct Normal
{
	float x, y, z; // Position
	float r, g, b; // Color
};

// Namespaces
using namespace std;
using namespace glm;

class Geometry
{
public:
	// ---------- Global Constants --------------

	// World data
	vec3 WorldPosition;
	vec3 WorldScale;
	float WorldRotationInDegrees;
	vec3 WorldRotationAxis;

	bool ShouldRender = true;

private:

	// ---------- Local Constants --------------

	unsigned int VAO, VBO, EBO;

	int numVertices = 0;

	// ---------- Global functions --------------

public:
	Geometry();

	virtual ~Geometry();

	virtual void Initialize();

	virtual void Initialize(vector<float>* geometry, int _numVariables);

	virtual void BeginPlayGeometry();

	virtual void TickVertexGeometry(float deltatime);

	virtual bool CheckCollision(Geometry* _otherObject);

	virtual void DoCollision(Geometry* _otherGeometry);

	virtual void drawVertexGeometry();

	virtual void Move(vec3 movementDirection, float deltatime);

	// Reading from file
	virtual vector<float>* InitializeVertexGeometryFromFile(const char* _filePath);

	virtual vector<float>* InitializeNormalGeometryFromFile(const char* _filePath);

private:

	// ---------- Local functions --------------

	// Bind data to buffers
	void bindBufferData(vector<float>* _vertices);

	void bindBufferData(vector<float> _vertices, vector<unsigned int> _indices);

	// Data attributes
	void CreateAttributePointers(bool pos);

	void CreateAttributePointers(bool pos, bool color);

	void CreateAttributePointers(bool pos, bool normals, bool color);

	// reading from file:

	vector<float>* genVerticesFromStruct(vector<Vertex*> _vertices);

	vector<float>* genNormalsFromNormalStruct(vector<Normal*> _normals);

	vector<Vertex*> readStructFromFile(const char* _filePath);

	vector<Normal*> readNormalStructFromFile(const char* _filePath);

	Vertex* CreateNewVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _r, float _g, float _b);

	Normal* CreateNewNormal(float _x, float _y, float _z, float _r, float _g, float _b);

	void writeVertexToConsole(vector<Vertex*> vectorToPrint);

	// ---------- Getters and setters --------------
public:
	virtual void SetShouldDraw(bool state);

};



#endif

