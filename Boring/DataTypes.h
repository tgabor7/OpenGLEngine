#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
using namespace std;

struct Animation2D {
	float speed = .1f;
	int rows = 1;
	int columns = 1;
	float time = 0;
	glm::vec2 pointer;
};
struct ModelData
{
	vector<float> vertices;
	vector<float> texture_coords;
	vector<float> normals;
	vector<int> indices;
};
struct Camera
{
	float angley;
	float anglex;
	float distance;
	glm::vec3 position;
	glm::vec3 pointToLookAt;
};
