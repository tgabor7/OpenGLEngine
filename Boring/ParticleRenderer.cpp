#include "ParticleRenderer.h"
#include <fstream>
#include <glm\gtc\type_ptr.hpp>

ParticleRenderer::ParticleRenderer(ModelData *data)
{
	this->vbo = Loader::createEmptyVBO(16 * 100000);
	this->vao = Loader::createVao({ 0, 1, 2 });
	draw_count = data->indices.size();
	Loader::storeDataInAttributeList(0, 3, &data->vertices[0], data->vertices.size());
	Loader::storeDataInAttributeList(1, 2, &data->texture_coords[0], data->texture_coords.size());
	Loader::storeDataInAttributeList(2, 3, &data->normals[0], data->normals.size());

	Loader::bindIndicesBuffer(&data->indices[0], data->indices.size());
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vbo = Loader::createEmptyVBO(3 * 1000000);
	svbo = Loader::createEmptyVBO(3 * 1000000);
	rvbo = Loader::createEmptyVBO(3 * 1000000);
	lifevbo = Loader::createEmptyVBO(1000000);

	Loader::addInstancedAttribute(vao, vbo, 3, 3, 0, 0);
	Loader::addInstancedAttribute(vao, svbo, 4, 3, 0, 0);
	Loader::addInstancedAttribute(vao, rvbo, 5, 3, 0, 0);

	Loader::addInstancedAttribute(vao, lifevbo, 6, 1, 0, 0);


	this->shader = new ParticleShader("shaders/particle");
}

void ParticleRenderer::render(ParticleSystem *particle_system, Camera c) {

	if (particle_system->models.size() == 0) return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	shader->bind();

	glActiveTexture(GL_TEXTURE0);;
	glBindTexture(GL_TEXTURE_2D, particle_system->tex->texture_id);
	glEnable(GL_BLEND);

	shader->setUniform("projection", functions::createProjectionMatrix(70, .1, 1000));
	mat4x4 viewmatrix = functions::createViewMatrix(c);
	shader->setUniform("view", viewmatrix);
	shader->setUniform("custom_color", particle_system->custom_color);
	shader->setUniform("billboard", (float)particle_system->billboard);
	shader->setUniform("rows", particle_system->rows);
	shader->setUniform("columns", particle_system->columns);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);



	vboData = vector<float>(particle_system->models.size() * 3);
	svbodata = vector<float>(particle_system->models.size() * 3);
	rvbodata = vector<float>(particle_system->models.size() * 3);

	lifedata = vector<float>(particle_system->models.size());
	int pointer = 0;
	int p = 0;
	int ps = 0;
	int pr = 0;
	for (int j = 0; j < particle_system->models.size(); j++) {


		//mat4x4 matrix = functions::createTransformationMatrix(quads[j]->position,quads[j]->rotation,quads[j]->scale);

		//if(billboard) matrix /= viewmatrix;

		vboData[pointer++] = particle_system->models[j]->position.x;
		vboData[pointer++] = particle_system->models[j]->position.y;
		vboData[pointer++] = particle_system->models[j]->position.z;

		svbodata[ps++] = particle_system->models[j]->scale.x;
		svbodata[ps++] = particle_system->models[j]->scale.y;
		svbodata[ps++] = particle_system->models[j]->scale.z;

		rvbodata[pr++] = particle_system->models[j]->rotation.x;
		rvbodata[pr++] = particle_system->models[j]->rotation.y;
		rvbodata[pr++] = particle_system->models[j]->rotation.z;


		lifedata[p++] = particle_system->models[j]->life;

	}
	Loader::updateVBO(rvbo, &rvbodata[0], rvbodata.size());

	Loader::updateVBO(svbo, &svbodata[0], svbodata.size());

	Loader::updateVBO(vbo, &vboData[0], vboData.size());

	Loader::updateVBO(lifevbo, &lifedata[0], lifedata.size());

	glDrawElementsInstanced(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0,
		particle_system->models.size());



	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	shader->unBind();
}
void ParticleRenderer::rebind(ModelData *data) {

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	this->vbo = Loader::createEmptyVBO(16 * 100000);
	this->vao = Loader::createVao({ 0, 1, 2 });
	draw_count = data->indices.size();
	Loader::storeDataInAttributeList(0, 3, &data->vertices[0], data->vertices.size());
	Loader::storeDataInAttributeList(1, 2, &data->texture_coords[0], data->texture_coords.size());
	Loader::storeDataInAttributeList(2, 3, &data->normals[0], data->normals.size());

	Loader::bindIndicesBuffer(&data->indices[0], data->indices.size());
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}
ParticleRenderer::~ParticleRenderer()
{
	delete shader;
}
