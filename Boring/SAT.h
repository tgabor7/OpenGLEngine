#pragma once
#include <glm/common.hpp>
#include <vector>
#include "System.h"
#include <glm/geometric.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace std;

class OBB : public Component<OBB> {
public:
	OBB() {}
	OBB(glm::vec3 position, glm::vec3 scale) {
		for (int i = 0; i < vertices.size(); i++) {
			this->vertices[i] *= scale;
			this->data[i] += position;
			this->offset = position;
		}
		color = glm::vec4(1, 1, 0, 1);
	}
	vector<glm::vec3> data = {
		glm::vec3(1,1,1),glm::vec3(-1,1,1),glm::vec3(1,-1,1),glm::vec3(-1,-1,1),
		glm::vec3(1,1,-1),glm::vec3(-1,1,-1),glm::vec3(1,-1,-1),glm::vec3(-1,-1,-1)
	};
	vector<glm::vec3> vertices = {
		glm::vec3(1,1,1),glm::vec3(-1,1,1),glm::vec3(1,-1,1),glm::vec3(-1,-1,1),
		glm::vec3(1,1,-1),glm::vec3(-1,1,-1),glm::vec3(1,-1,-1),glm::vec3(-1,-1,-1)
	};
	glm::vec3 offset;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec4 color;
private:
	
};

class SAT : public System
{
public:
	SAT();
	static bool collide(int a, int b);
	void updateComponents(double delta);
	void updateSystem(double delta);
	~SAT();
private:
	static vector<float> createDots(glm::vec3 axis,vector<glm::vec3> vertices);
	static float getMin(vector<float> data);
	static float getMax(vector<float> data);
};

