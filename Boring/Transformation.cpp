#include "Transformation.h"
#include <glm/vec3.hpp>


Transformation::Transformation()
{
	this->scale = glm::vec3(1);
	this->pos = glm::vec3();
}


Transformation::~Transformation()
{
}
