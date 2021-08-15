#pragma once
#include <GL/glew.h>
#include "EntityHandler.h"
#include "DataTypes.h"
#include "Texture.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
class Mesh : public Component<Mesh>
{
public:
	Mesh();
	Mesh(ModelData data);
	ModelData data;
	GLuint vao;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec4 color;
	glm::vec4 outLineColor;
	Texture *texture;
	bool has_shadow;
	int draw_count;
	~Mesh();
};

