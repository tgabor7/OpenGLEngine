#pragma once
#include <glm\vec3.hpp>
class Vertex
{
	const static int NO_INDEX = -1;
public:

	Vertex(int index, glm::vec3 position);

	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) {
		return textureIndexOther == this->textureIndex && normalIndexOther == this->normalIndex;
	}
	int getTextureIndex();
	void setTextureIndex(int i);

	int getNormalIndex();
	void setNormalIndex(int i);


	float getLength() {
		return this->length;
	}
	void setLength(float f) {
		this->length = f;
	}
	glm::vec3 getPosition() {
		return this->position;
	}
	void setPosition(glm::vec3 p) {
		this->position = p;
	}
	int getIndex() {
		return this->index;
	}
	Vertex* getDuplicateVertex();
	void setDuplicateVertex(Vertex* d);
	~Vertex();
private:
	glm::vec3 position;
	int textureIndex = -1;
	int normalIndex = -1;
	Vertex* duplicateVertex = nullptr;
	int index;
	float length;
};

