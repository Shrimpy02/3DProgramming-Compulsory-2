#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include "glm/vec3.hpp"
#include <iostream>


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

// Forward Declerations
class Shader;

// Namespaces
using namespace std;
using namespace glm;

class Geometry
{
public:
	// ---------- Global Constants --------------

	vec3 WorldPosition;
	vec3 WorldScale;
	bool ShouldRender = true;
private:

	// ---------- Local Constants --------------

	unsigned int VAO, VBO, EBO;

	int numVertices = 0;

	bool doneonce = false;



	// ---------- Global functions --------------

public:
	Geometry();

	virtual ~Geometry();

	virtual void Initialize();

	void Initialize(vector<float>* geometry, int _numVariables);

	virtual void drawVertexGeometry();

	vector<float>* InitializeVertexGeometryFromFile(const char* _filePath);

	vector<float>* InitializeNormalGeometryFromFile(const char* _filePath);

	void bindBufferData(vector<float> _vertices);

	void bindBufferData(vector<float>* _vertices);

	void bindBufferData(vector<float> _vertices, vector<unsigned int> _indices);

	void createAttributePointers(bool pos);

	void createAttributePointers(bool pos, bool color);

	void createAttributePointers(bool pos, bool normals, bool color);

	// added afterwards; needs cleaning:

	virtual void TickVertexGeometry();

	virtual void Move(vec3 movementDirection, float deltatime);

	virtual bool CheckCollision(Geometry* _otherObject);

	virtual void DoCollision(Geometry* _otherGeometry);

	virtual bool ShouldDraw();

private:

	// ---------- Local functions --------------

	vector<float>* genVerticesFromStruct(vector<Vertex*> _vertices);

	vector<float>* genNormalsFromStruct(vector<Normal*> _normals);

	vector<unsigned int> GenerateIndices(vector<Vertex*> _vertices);

	vector<Vertex*> readVerticesFromFile(const char* _filePath);

	vector<Normal*> readNormalsFromFile(const char* _filePath);

	Vertex* CreateNewVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _r, float _g, float _b);

	Normal* CreateNewNormal(float _x, float _y, float _z, float _r, float _g, float _b);

	void writeVertexToConsole(vector<Vertex*> vectorToPrint);

	// ---------- Getters and setters --------------
public:


};



#endif

