#include "DefaultSphere.h"
#include "Shader.h"

#include "glm/glm.hpp"

DefaultSphere::DefaultSphere()
{
}

DefaultSphere::DefaultSphere(Shader* _shader, vec3 _worldPosition, vec3 _worldScale, float _worldRotationInDegrees, vec3 _worldRotationAxis)
{
	ObjectShader = _shader;
	WorldPosition = _worldPosition;
	WorldScale = _worldScale;
	WorldRotationInDegrees = _worldRotationInDegrees;
	WorldRotationAxis = _worldRotationAxis;
}

void DefaultSphere::Initialize()
{
	vec3 v0 = vec3(0, 0, 1);
	vec3 v1 = vec3(1, 0, 0);
	vec3 v2 = vec3(0, 1, 0);
	vec3 v3 = vec3(-1, 0, 0);
	vec3 v4 = vec3(0, -1, 0);
	vec3 v5 = vec3(0, 0, -1);


	SubDivide(v0,v1,v2, NumSubDivides);
	SubDivide(v0, v2, v3, NumSubDivides);
	SubDivide(v0, v3, v4, NumSubDivides);
	SubDivide(v0, v4, v1, NumSubDivides);

	SubDivide(v5, v2, v1, NumSubDivides);
	SubDivide(v5, v3, v2, NumSubDivides);
	SubDivide(v5, v4, v3, NumSubDivides);
	SubDivide(v5, v1, v4, NumSubDivides);

	makeSphere();

	Geometry::Initialize(&SphereVertices, NumVariables);
}

void DefaultSphere::drawVertexGeometry()
{
	if (ObjectShader)
	{
		ObjectShader->use();
		ObjectShader->processTransformations(WorldPosition, WorldScale, WorldRotationInDegrees, WorldRotationAxis);
	}

	Geometry::drawVertexGeometry();
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

void DefaultSphere::TickVertexGeometry()
{
}
