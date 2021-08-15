#pragma once
#include <glm\mat4x4.hpp>

using namespace glm;

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	void normalize();
	float x, y, z, w;
	mat4x4 toRotationMatrix();
	~Quaternion();
};

