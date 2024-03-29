// Class includes
#include "Geometry.h"
#include "Shader.h"

// Name Space
using namespace std;
using namespace glm;

Geometry::Geometry()
{

}

Geometry::~Geometry()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Geometry::Initialize()
{
	cout << "Geometry Initialized without Vertex Data" << endl;
}

void Geometry::Initialize(vector<float>* geometry, int _numVariables)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	numVertices = geometry->size() / _numVariables;

	switch (_numVariables)
	{
	case 3:
		bindBufferData(geometry);
		CreateAttributePointers(true);
		break;
	case 6:
		bindBufferData(geometry);
		CreateAttributePointers(true, true);
		break;
	case 9:
		bindBufferData(geometry);
		CreateAttributePointers(true, true, true);
		break;
	default:
		cout << "ERROR NUM VARIABLES NOT CORRECT \n";
		break;
	}
}

void Geometry::BeginPlayGeometry()
{
}

void Geometry::TickVertexGeometry(float deltatime)
{
}

bool Geometry::CheckCollision(Geometry* _otherObject)
{
	// Should be local logic specified to it`s geometry
	cout << "Empty Collision Checker\n";
	return false;
}

void Geometry::DoCollision(Geometry* _otherGeometry)
{
	// Should be local logic specified to it`s geometry
	cout << "Empty Collision Do`er\n";
}

void Geometry::drawVertexGeometry()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glBindVertexArray(0);
}

void Geometry::Move(vec3 movementDirection, float deltatime)
{
	WorldPosition += (movementDirection * deltatime) / vec3(10, 10, 10);
}

// ---------- Local functions --------------

void Geometry::bindBufferData(vector<float>* _vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices->size() * sizeof(float), _vertices->data(), GL_STATIC_DRAW);
}

void Geometry::bindBufferData(vector<float> _vertices, vector<unsigned int> _indices)
{

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices.data()), _vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices.data()), _indices.data(), GL_STATIC_DRAW);

}

void Geometry::CreateAttributePointers(bool pos)
{
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Geometry::CreateAttributePointers(bool pos, bool color)
{
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Geometry::CreateAttributePointers(bool pos, bool normals, bool color)
{
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// color
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

// Reading from file:

vector<float>* Geometry::InitializeVertexGeometryFromFile(const char* _filePath)
{
	return genVerticesFromStruct(readStructFromFile(_filePath));
}

vector<float>* Geometry::InitializeNormalGeometryFromFile(const char* _filePath)
{
	return genNormalsFromNormalStruct(readNormalStructFromFile(_filePath));
}

vector<float>* Geometry::genVerticesFromStruct(vector<Vertex*> _vertices)
{
	vector<float>* temp = new vector<float>;
	for (int i = 0; i < _vertices.size(); i++)
	{
		temp->push_back(_vertices[i]->x);
		temp->push_back(_vertices[i]->y);
		temp->push_back(_vertices[i]->z);
		temp->push_back(_vertices[i]->nx);
		temp->push_back(_vertices[i]->ny);
		temp->push_back(_vertices[i]->nz);
		temp->push_back(_vertices[i]->r);
		temp->push_back(_vertices[i]->g);
		temp->push_back(_vertices[i]->b);
	}
	return temp;
}

vector<float>* Geometry::genNormalsFromNormalStruct(vector<Normal*> _normals)
{
	vector<float>* temp = new vector<float>;
	for (int i = 0; i < _normals.size(); i++)
	{
		temp->push_back(_normals[i]->x);
		temp->push_back(_normals[i]->y);
		temp->push_back(_normals[i]->z);
		temp->push_back(_normals[i]->r);
		temp->push_back(_normals[i]->g);
		temp->push_back(_normals[i]->b);
	}
	return temp;
}

vector<Vertex*> Geometry::readStructFromFile(const char* _filePath)
{
	ifstream GeometryFile;
	// Open the txt file containing geometry data.
	GeometryFile.open(_filePath);

	// First line defines how many lines there are total
	// Extract and convert to int
	string numLinesStr;
	getline(GeometryFile, numLinesStr);
	int numLinesInt = stoi(numLinesStr);

	string numVariablesStr;
	getline(GeometryFile, numVariablesStr);
	int numVariablesInt = stoi(numVariablesStr);

	// Create a vector to contain all vertexes generated. 
	vector<Vertex*> temp;

	// Iterates through the total number of lines. 
	for (int i = 0; i < numLinesInt; i++)
	{
		// Gets the first line as a string, removes all spaces and parentheses
		string tempLines, result1, result2, result3;
		getline(GeometryFile, tempLines);
		std::remove_copy(tempLines.begin(), tempLines.end(), std::back_inserter(result1), ' ');
		std::remove_copy(result1.begin(), result1.end(), std::back_inserter(result2), '(');
		std::remove_copy(result2.begin(), result2.end(), std::back_inserter(result3), ')');

		// Pre defines variables for converting from string to float.
		float x = 0, y = 0, z = 0, nx = 0, ny = 0, nz = 0, r = 0, g = 0, b = 0;

		// Iterates through number of variables in current line
		for (int i = 0; i < numVariablesInt; i++)
		{
			// Gets the index between start and first number end defined by ','.
			int lastPosNumIndex = result3.find(',');
			// Copies this value into sting
			string final(result3.begin(), result3.begin() + lastPosNumIndex);
			// Erases that value from complete string
			result3.erase(result3.begin(), result3.begin() + lastPosNumIndex + 1);

			// Switch case to convert value to proper variable
			switch (i + 1)
			{
			case 1:
				x = stof(final);
				break;
			case 2:
				y = stof(final);
				break;
			case 3:
				z = stof(final);
				break;
			case 4:
				nx = stof(final);
				break;
			case 5:
				ny = stof(final);
				break;
			case 6:
				nz = stof(final);
				break;
			case 7:
				r = stof(final);
				break;
			case 8:
				g = stof(final);
				break;
			case 9:
				b = stof(final);
				break;
			default:
				// Error handling if default case triggered. 
				cout << "ERROR::READING_GEOMETRY_FILE::NO_MORE_VERTEX_ATTRIBUTE_LINES";
				break;
			}

		}

		// creates the new vertex with the given variables.
		temp.push_back(CreateNewVertex(x, y, z, nx, ny, nz, r, g, b));
	}

	// close file when finished reading it
	GeometryFile.close();

	return temp;
}

vector<Normal*> Geometry::readNormalStructFromFile(const char* _filePath)
{
	ifstream GeometryFile;
	// Open the txt file containing geometry data.
	GeometryFile.open(_filePath);

	// First line defines how many lines there are total
	// Extract and convert to int
	string numLinesStr;
	getline(GeometryFile, numLinesStr);
	int numLinesInt = stoi(numLinesStr);

	string numVariablesStr;
	getline(GeometryFile, numVariablesStr);
	int numVariablesInt = stoi(numVariablesStr);

	// Create a vector to contain all vertexes generated. 
	vector<Normal*> temp;

	// Iterates through the total number of lines. 
	for (int i = 0; i < numLinesInt; i++)
	{
		// Gets the first line as a string, removes all spaces and parentheses
		string tempLines, result1, result2, result3;
		getline(GeometryFile, tempLines);
		std::remove_copy(tempLines.begin(), tempLines.end(), std::back_inserter(result1), ' ');
		std::remove_copy(result1.begin(), result1.end(), std::back_inserter(result2), '(');
		std::remove_copy(result2.begin(), result2.end(), std::back_inserter(result3), ')');

		// Pre defines variables for converting from string to float.
		float x = 0, y = 0, z = 0, r = 0, g = 0, b = 0;

		// Iterates through number of variables in current line
		for (int i = 0; i < numVariablesInt; i++)
		{
			// Gets the index between start and first number end defined by ','.
			int lastPosNumIndex = result3.find(',');
			// Copies this value into sting
			string final(result3.begin(), result3.begin() + lastPosNumIndex);
			// Erases that value from complete string
			result3.erase(result3.begin(), result3.begin() + lastPosNumIndex + 1);

			// Switch case to convert value to proper variable
			switch (i + 1)
			{
			case 1:
				x = stof(final);
				break;
			case 2:
				y = stof(final);
				break;
			case 3:
				z = stof(final);
				break;
			case 4:
				r = stof(final);
				break;
			case 5:
				g = stof(final);
				break;
			case 6:
				b = stof(final);
				break;
			default:
				// Error handling if default case triggered. 
				cout << "ERROR::READING_GEOMETRY_FILE::NO_MORE_VERTEX_ATTRIBUTE_LINES";
				break;
			}

		}

		// creates the new vertex with the given variables.
		temp.push_back(CreateNewNormal(x, y, z, r, g, b));
	}

	// close file when finished reading it
	GeometryFile.close();

	return temp;
}

Vertex* Geometry::CreateNewVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _r, float _g, float _b)
{
	Vertex* NewVertex = new Vertex();
	NewVertex->x = _x;
	NewVertex->y = _y;
	NewVertex->z = _z;
	NewVertex->nx = _nx;
	NewVertex->ny = _ny;
	NewVertex->nz = _nz;
	NewVertex->r = _r;
	NewVertex->g = _g;
	NewVertex->b = _b;
	return NewVertex;
}

Normal* Geometry::CreateNewNormal(float _x, float _y, float _z, float _r, float _g, float _b)
{
	Normal* NewNormal = new Normal();
	NewNormal->x = _x;
	NewNormal->y = _y;
	NewNormal->z = _z;
	NewNormal->r = _r;
	NewNormal->g = _g;
	NewNormal->b = _b;
	return NewNormal;
}

void Geometry::writeVertexToConsole(vector<Vertex*> vectorToPrint)
{
	for (int i = 0; i < vectorToPrint.size(); i++)
	{
		cout << "x = " << vectorToPrint[i]->x << ", ";
		cout << "y = " << vectorToPrint[i]->y << ", ";
		cout << "z = " << vectorToPrint[i]->z << ", ";
		cout << "r = " << vectorToPrint[i]->r << ", ";
		cout << "g = " << vectorToPrint[i]->g << ", ";
		cout << "b = " << vectorToPrint[i]->b << ", ";
		cout << endl;
	}
}

// ---------- Getters and Setters --------------

void Geometry::SetShouldDraw(bool state)
{
	ShouldRender = state;
}
