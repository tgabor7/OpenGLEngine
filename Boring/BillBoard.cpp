#include "BillBoard.h"



BillBoard::BillBoard()
{
}
BillBoard::BillBoard(Texture *texture, glm::vec3 position, glm::vec2 scale, float rotation)
{
	ModelData data = OBJLoader::loadOBJ("objs/plane.obj");
	this->texture = texture;
	draw_count = data.indices.size();
	color = glm::vec4(0);
	this->texture = texture;
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint v_vbo;
	glGenBuffers(1, &v_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.vertices.size(), &data.vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint t_vbo;
	glGenBuffers(1, &t_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.texture_coords.size(), &data.texture_coords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint n_vbo;
	glGenBuffers(1, &n_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.normals.size(), &data.normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint i_vbo;
	glGenBuffers(1, &i_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLint), &data.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


BillBoard::~BillBoard()
{
}
