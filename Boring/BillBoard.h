#pragma once
#include "Texture.h"

#include "EntityHandler.h"
#include "OBJLoader.h"
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class BillBoard : public Component<BillBoard>
{
public:
	BillBoard();
	BillBoard(Texture *texture, glm::vec3 position, glm::vec2 scale, float rotation);
	int draw_count;
	glm::vec4 color;
	Texture *texture;
	GLuint vao;
	glm::vec3 position;
	glm::vec2 scale;
	float rotation;
	~BillBoard();
};

