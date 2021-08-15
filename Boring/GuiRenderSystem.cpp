#include "GuiRenderSystem.h"



GuiRenderSystem::GuiRenderSystem()
{
	shader = Shader("shaders/gui");
	ModelData data = OBJLoader::loadOBJ("objs/cube.obj");
	this->vbo = Loader::createEmptyVBO(16 * 100000);
	this->vao = Loader::createVao({ 0, 1, 2 });
	projection = glm::ortho(0.f, (float)State::WIDTH, (float)State::HEIGHT, 0.f);

	draw_count = data.indices.size();
	Loader::storeDataInAttributeList(0, 3, &data.vertices[0], data.vertices.size());
	Loader::storeDataInAttributeList(1, 2, &data.texture_coords[0], data.texture_coords.size());
	Loader::storeDataInAttributeList(2, 3, &data.normals[0], data.normals.size());

	Loader::bindIndicesBuffer(&data.indices[0], data.indices.size());
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	Loader::addInstancedAttribute(vao, vbo, 3, 4, 16, 0);
	Loader::addInstancedAttribute(vao, vbo, 4, 4, 16, 4);
	Loader::addInstancedAttribute(vao, vbo, 5, 4, 16, 8);
	Loader::addInstancedAttribute(vao, vbo, 6, 4, 16, 12);
}
void GuiRenderSystem::updateComponents(double delta)
{

}
void GuiRenderSystem::updateSystem(double delta)
{
	vector<GUIComponent> guis = getComponents<GUIComponent>();
	if (guis.size() == 0) return;
	shader.bind();
	shader.setUniform("projection", projection);

	glBindVertexArray(this->vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);

	pointer = 0;
	vboData = vector<float>(guis.size() * 16);

	for (GUIComponent m : guis) {
		bindTexture(m.texture);
		updateModelViewMatrix(vec3(m.position.x, m.position.y, 0), 0, 0, m.roatation, m.scale.x, m.scale.y, 1, 1.0f, &vboData[0]);
	}

	Loader::updateVBO(this->vbo, &vboData[0], vboData.size());
	glDrawElementsInstanced(GL_TRIANGLES, this->draw_count, GL_UNSIGNED_INT, 0,
		guis.size());
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	shader.unBind();
}
void GuiRenderSystem::updateModelViewMatrix(vec3 position, float rx, float ry, float rz, float width, float height, float length, float scale, float * vboData)
{
	storeMatrixData(functions::createTransformationMatrix(position, vec3(rx, ry, rz), vec3(width, height, length)), vboData);
}
void GuiRenderSystem::bindTexture(Texture *texture)
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture_id);
}
void GuiRenderSystem::storeMatrixData(mat4x4 matrix, float * vboData)
{
	vboData[pointer++] = matrix[0][0];
	vboData[pointer++] = matrix[0][1];
	vboData[pointer++] = matrix[0][2];
	vboData[pointer++] = matrix[0][3];
	vboData[pointer++] = matrix[1][0];
	vboData[pointer++] = matrix[1][1];
	vboData[pointer++] = matrix[1][2];
	vboData[pointer++] = matrix[1][3];
	vboData[pointer++] = matrix[2][0];
	vboData[pointer++] = matrix[2][1];
	vboData[pointer++] = matrix[2][2];
	vboData[pointer++] = matrix[2][3];
	vboData[pointer++] = matrix[3][0];
	vboData[pointer++] = matrix[3][1];
	vboData[pointer++] = matrix[3][2];
	vboData[pointer++] = matrix[3][3];
}
GuiRenderSystem::~GuiRenderSystem()
{
}
