#include "Light.h"


Light::Light(vec3 pos, vec3 color, vec3 att)
{
	this->position = pos;
	this->color = color;
	this->attenuation = att;
}
Light::Light()
{
}


Light::~Light()
{
}
