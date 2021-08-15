#include "InstanceRenderSystem.h"
#include "Loader.h"
#include "Mesh.h"
#include "State.h"

InstanceComponent::InstanceComponent(ModelData data)
{
	this->data = data;
	this->vbo = Loader::createEmptyVBO(16 * 100000);
	this->vao = Loader::createVao({ 0, 1, 2 });
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
	rotation = true;
}
InstanceComponent::InstanceComponent(ModelData data,bool rot)
{
	this->data = data;
	this->vbo = Loader::createEmptyVBO(16 * 100000);
	this->vao = Loader::createVao({ 0, 1, 2 });
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
	rotation = rot;
}
void InstanceComponent::addInstance(MeshInstance instance)
{
	this->meshes.push_back(instance);
	if (std::find(textures.begin(), textures.end(), instance.texture) == textures.end()) {
		textures.push_back(instance.texture);
	}
}
void InstanceComponent::addInstance(vec3 position, vec3 rotation, vec3 scale, Texture *texture)
{
	addInstance({ position,rotation,scale,texture });
	if (std::find(textures.begin(), textures.end(), texture) == textures.end()) {
		textures.push_back(texture);
	}
}
void InstanceComponent::removeInstance(int id)
{
	this->meshes.erase(meshes.begin() + id);
}
InstanceRenderSystem::InstanceRenderSystem()
{
	this->shader = Shader("shaders/instance");
}
void InstanceRenderSystem::update(double delta)
{

	vector<InstanceComponent> models = getComponents<InstanceComponent>();
	for (int i = 0; i < models.size(); i++) {
		if (models[i].meshes.size() <= 0) break;
		for (Texture *t : models[i].textures) {
			shader.bind();
			mat4x4 viewMatrix = functions::createViewMatrix(State::camera);
			mat4x4 projectionMatrix = functions::createProjectionMatrix(70, .1, 1000.f);
			shader.setUniform("projection", projectionMatrix);
			shader.setUniform("view", viewMatrix);
			glBindVertexArray(models[i].vao);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);
			glEnableVertexAttribArray(6);

			pointer = 0;
			vboData = vector<float>(models[i].meshes.size() * 16);
			bindTexture(t);
			mat4x4 transformation = mat4x4();
			for (MeshInstance m : models[i].meshes) {

				if (models[i].rotation) {
					updateModelViewMatrix(m.position, m.rotation.x, m.rotation.y, m.rotation.z, m.scale.x, m.scale.y, m.scale.z, 1.0f, &vboData[0]);
				}
				else {
					storeMatrixData(transformation, &vboData[0]);
				}
			}

			Loader::updateVBO(models[i].vbo, &vboData[0], vboData.size());
			glDrawElementsInstanced(GL_TRIANGLES, models[i].draw_count, GL_UNSIGNED_INT, 0,
				models[i].meshes.size());
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

	}

}
void InstanceRenderSystem::updateModelViewMatrix(vec3 position, float rx, float ry, float rz, float width, float height, float length, float scale, float * vboData)
{
	storeMatrixData(functions::createTransformationMatrix(position, vec3(rx, ry, rz), vec3(width, height, length)), vboData);
}
void InstanceRenderSystem::bindTexture(Texture *texture)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->texture_id);
}
void InstanceRenderSystem::storeMatrixData(mat4x4 matrix, float * vboData)
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
InstanceRenderSystem::~InstanceRenderSystem()
{
}
