// Class includes
#include "DefaultSphere.h"
#include "Shader.h"

// C++ includes
#include "glm/glm.hpp"

DefaultSphere::DefaultSphere()
{
}

DefaultSphere::DefaultSphere(Shader* _shader, int _numSubDivides, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	NumSubDivides = _numSubDivides;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

DefaultSphere::~DefaultSphere()
{
	Geometry::~Geometry();
}

void DefaultSphere::Initialize()
{
	GenerateSphere(NumSubDivides);

	Geometry::Initialize(&SphereVertices, NumVariables);
}

void DefaultSphere::BeginPlayGeometry()
{
	Geometry::BeginPlayGeometry();
}

void DefaultSphere::TickVertexGeometry(float deltatime)
{
	Geometry::TickVertexGeometry(deltatime);
}

bool DefaultSphere::CheckCollision(Geometry* _otherGeometry)
{
	// Check Collision logic
	return false;
}

void DefaultSphere::DoCollision(Geometry* _otherGeometry)
{
	// Do Collision logic
	cout << "No Do CollisionLogic for this object type\n";
}

void DefaultSphere::drawVertexGeometry()
{
	if (ShouldRender)
	{
		if (ObjectShader)
		{
			ObjectShader->use();
			ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
		}

		Geometry::drawVertexGeometry();
	}
}

void DefaultSphere::Move(vec3 movementDirection, float deltatime)
{
	Geometry::Move(movementDirection, deltatime);
}

// ---------- Local functions --------------

void DefaultSphere::GenerateSphere(int _numSubDivides)
{
	vec3 v0 = vec3(0, 0, 1);
	vec3 v1 = vec3(1, 0, 0);
	vec3 v2 = vec3(0, 1, 0);
	vec3 v3 = vec3(-1, 0, 0);
	vec3 v4 = vec3(0, -1, 0);
	vec3 v5 = vec3(0, 0, -1);


	SubDivide(v0, v1, v2, _numSubDivides);
	SubDivide(v0, v2, v3, _numSubDivides);
	SubDivide(v0, v3, v4, _numSubDivides);
	SubDivide(v0, v4, v1, _numSubDivides);

	SubDivide(v5, v2, v1, _numSubDivides);
	SubDivide(v5, v3, v2, _numSubDivides);
	SubDivide(v5, v4, v3, _numSubDivides);
	SubDivide(v5, v1, v4, _numSubDivides);

	makeSphere();
}

void DefaultSphere::SubDivide(const vec3& a, const vec3& b, const vec3& c, int n)
{
	if (n > 0)
	{
		vec3 v1 = a + b;
		v1 = normalize(v1);

		vec3 v2 = a + c;
		v2 = normalize(v2);

		vec3 v3 = c + b;
		v3 = normalize(v3);

		SubDivide(a, v1, v2, n - 1);
		SubDivide(v1, b, v3, n - 1);
		SubDivide(v2, v3, c, n - 1);
		SubDivide(v1, v3, v2, n - 1);
	}
	else
	{
		MakeTriangle(a, b, c);
	}
}

void DefaultSphere::MakeTriangle(const vec3& _a, const vec3& _b, const vec3& _c)
{
	Vertex* v = new Vertex{ _a.x,_a.y,_a.z,_a.x,_a.y,_a.z, r, g, b };
	SphereVerticesStruct.push_back(v);
	v = new Vertex{ _b.x,_b.y,_b.z,_b.x,_b.y,_b.z, r, g, b };
	SphereVerticesStruct.push_back(v);
	v = new Vertex{ _c.x,_c.y,_c.z,_c.x,_c.y,_c.z, r, g, b };
	SphereVerticesStruct.push_back(v);
}

void DefaultSphere::makeSphere()
{
	for (int i = 0; i < SphereVerticesStruct.size(); i++)
	{
		SphereVertices.push_back(SphereVerticesStruct[i]->x);
		SphereVertices.push_back(SphereVerticesStruct[i]->y);
		SphereVertices.push_back(SphereVerticesStruct[i]->z);
		SphereVertices.push_back(SphereVerticesStruct[i]->nx);
		SphereVertices.push_back(SphereVerticesStruct[i]->ny);
		SphereVertices.push_back(SphereVerticesStruct[i]->nz);
		SphereVertices.push_back(SphereVerticesStruct[i]->r);
		SphereVertices.push_back(SphereVerticesStruct[i]->g);
		SphereVertices.push_back(SphereVerticesStruct[i]->b);
	}
}

// ---------- Getters and setters --------------

void DefaultSphere::SetShouldDraw(bool state)
{
	ShouldRender = state;
}

