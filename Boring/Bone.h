#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include "Quaternion.h"


using namespace glm;

struct Bone {

	vec3 position;
	Quaternion rotation;
	const char* name;
	mat4x4 bindMatrix;
};