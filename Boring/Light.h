#pragma once
#include "EntityHandler.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

class Light : public Component<Light>
{
public:
	Light();
	Light(glm::vec3 pos, glm::vec3 color, glm::vec3 att);
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 attenuation;
	~Light();
};

