#include "AnimatedMesh.h"
#include "Loader.h"
#include <GL\glew.h>


AnimatedMesh::AnimatedMesh() {}
AnimatedMesh::AnimatedMesh(vec3 position, ModelData *data, Animation animation, vec3 transformation, Texture *texture)
{
	this->data = data;
	this->position = position;
	this->transformation = transformation;
	this->rotation = vec3();
	this->texture = texture;
	this->customColor = vec4(0);
	this->animation = animation;

	VertexArrayID = Loader::createVao({ 0,1,2,3,4 });


	draw_count = data->indices.size();
	Loader::storeDataInAttributeList(0, 3, &data->vertices[0], data->vertices.size());
	Loader::storeDataInAttributeList(1, 2, &data->texture_coords[0], data->texture_coords.size());
	Loader::storeDataInAttributeList(2, 3, &data->normals[0], data->normals.size());
	Loader::storeDataInAttributeList(3, 4, (GLuint*)&animation.jointIndices[0], animation.jointIndices.size());
	Loader::storeDataInAttributeList(4, 4, &animation.weights[0], animation.weights.size());
	Loader::bindIndicesBuffer(&data->indices[0], data->indices.size());
	this->bones = animation.frames[0].bones;
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void AnimatedMesh::prepare() {
	glBindVertexArray(VertexArrayID);
}
void AnimatedMesh::render() {
	glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);
}
void AnimatedMesh::setFrame(int i) {
	animation.setFrames(i);
	this->bones = this->animation.frames[i].bones;
}
void AnimatedMesh::unBind() {
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
AnimatedMesh::~AnimatedMesh()
{
}
