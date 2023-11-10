#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
using namespace glm;
struct Vertex
{
	vec3 Position;
	vec2 TextureCoord;
	vec3 normal;
	vec3 Tangent;
	vec3 BiTangent;
	Vertex() {};
	
	Vertex(const Vertex &vert)
	{
		this->Position.x = vert.Position.x;
		this->Position.y = vert.Position.y;
		this->Position.z = vert.Position.z;

		TextureCoord = { vert.TextureCoord.x, vert.TextureCoord.y };

		Tangent = vec3(0);
		BiTangent = vec3(0);

	}
	Vertex(float x, float y, float z)
	{
		this->Position.x = x;
		this->Position.y = y;
		this->Position.z = z;
	}
	Vertex(const vec3 position) : Vertex(position.x, position.y, position.z)
	{

	}

	Vertex(const vec3 position, const vec2 texCoord)
	{
		this->Position = position;
		this->TextureCoord = texCoord;
	}
};

#endif