#include "ClothSystem.h"
#include "stb_image.h"


ClothSystem::ClothSystem()
{
	data = OBJLoader::loadOBJ("objs/plane.obj");
	vertices = &data.vertices[0];
	shader = new Shader("shaders/cloth", { {0,"position"} });
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	GLuint i_vbo;
	glGenBuffers(1, &i_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLint), &data.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	transformation = functions::createTransformationMatrix(vec3(0,5,0),vec3(),vec3(1));
	projection = functions::createProjectionMatrix(70, .1, 1000);

	

}
void ClothSystem::updateComponents(double delta)
{
	
}
void ClothSystem::updateSystem(double delta)
{
	glDisable(GL_CULL_FACE);
	shader->bind();
	shader->setUniform("transformation", transformation);
	shader->setUniform("view", functions::createViewMatrix(State::camera));
	shader->setUniform("projection",projection);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.vertices.size(), &data.vertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	shader->unBind();

	for (int i = 0; i < data.vertices.size() / 3; i+=3) {
		vec3 v = vec3(data.vertices[i], data.vertices[i + 1], data.vertices[i + 2]);
		

	}
	if (State::input->isKeyDown(keys::KEY_A)) {
		data.vertices[0] -= .01f;
	}
}
ClothSystem::~ClothSystem()
{
}
