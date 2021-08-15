#pragma once
#include "EntityHandler.h"
#include <glm/vec3.hpp>

class Transformation : public Component<Transformation>
{
public:
	Transformation();
	glm::vec3 pos;
	glm::vec3 rotation;
	glm::vec3 scale;
	~Transformation();
};

