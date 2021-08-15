#pragma once
#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include "Vertex.h"
#include <vector>
#include "DataTypes.h"
#include <string>

class OBJLoader
{
public:

	static ModelData loadOBJ(const char* path);
	static ModelData *loadOBJp(const char* path);
	static void processVertex(std::string vertex, std::vector<Vertex> &vertices, std::vector<int> &indices);
	static void dealWithAlreadyProcessedVertex(Vertex &previousVertex, int newTextureIndex,
		int newNormalIndex, std::vector<int> &indices, std::vector<Vertex> &vertices);
	static void removeUnusedVertices(std::vector<Vertex> &vertices);

	static float convertDataToArrays(std::vector<Vertex> &vertices, std::vector<glm::vec2> &textures,
		std::vector<glm::vec3> &normals, float *verticesArray, float *texturesArray,
		float *normalsArray, std::vector<float> &out_vertices,
		std::vector<int>& out_indices,
		std::vector<float>& out_uvs,
		std::vector<float> &out_normals);

};

