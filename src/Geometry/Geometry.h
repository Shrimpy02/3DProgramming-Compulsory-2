#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <vector>
#include "glm/vec3.hpp"


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

	void drawVertexGeometry(bool _useIndices, Shader* shaderToUse);

	void drawVertexGeometry(bool _useIndices, Shader* shaderToUse, vec3 positionOffset);

	void drawVertexGeometry(bool _useIndices, Shader* shaderToUse, vec3 positionOffset, vec3 scaleOffset);

	void drawVertexGeometry(bool _useIndices, Shader* shaderToUse, vec3 positionOffset, vec3 scaleOffset, float rotationOffset, vec3 rotationAxis);

	void drawNormalGeometry(Shader* shaderToUse, vec3 positionOffset, vec3 scaleOffset, float rotationOffset, vec3 rotationAxis);

	vector<float>* generateVertexGeometryFromFile(const char* _filePath);

	vector<float>* generateNormalGeometryFromFile(const char* _filePath);

	void bindBufferData(vector<float> _vertices);

	void bindBufferData(vector<float>* _vertices);

	void bindBufferData(vector<float> _vertices, vector<unsigned int> _indices);

	void createAttributePointers(bool pos);

	void createAttributePointers(bool pos, bool color);

	void createAttributePointers(bool pos, bool normals, bool color);

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
