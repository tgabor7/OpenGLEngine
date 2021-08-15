#include "Vertex.h"



Vertex::Vertex(int index, glm::vec3 position)
{
	Vertex::index = index;
	Vertex::position = position;
	Vertex::length = position.length();

}

bool Vertex::isSet() {
	return textureIndex != -1 && normalIndex != -1;
}
int Vertex::getTextureIndex() {
	return this->textureIndex;
}
void Vertex::setTextureIndex(int i) {
	this->textureIndex = i;
}
int Vertex::getNormalIndex() {
	return this->normalIndex;
}
void Vertex::setNormalIndex(int i) {
	this->normalIndex = i;
}
void Vertex::setDuplicateVertex(Vertex* v) {
	this->duplicateVertex = v;
}
Vertex* Vertex::getDuplicateVertex() {
	return this->duplicateVertex;
}

Vertex::~Vertex()
{
}
