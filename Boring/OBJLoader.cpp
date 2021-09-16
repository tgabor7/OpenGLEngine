#include "OBJLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <glm\vec3.hpp>
#include "Vertex.h"

using namespace std;

ModelData OBJLoader::loadOBJ(const char* path) {

	std::vector<Vertex> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tex_coords;
	std::vector<int> indices;

	std::vector<float> out_vertices;
	std::vector<int> out_indices;
	std::vector<float> out_uvs;
	std::vector<float> out_normals;

	ifstream file;
	file.open(path);
	string output;
	if (file.is_open()) {

		std::string line;

		while (getline(file, line)) {

			if (line.substr(0, line.find(' ')) == "v") {

				line.erase(0, 1);
				glm::vec3 vertex;
				stringstream line_s = stringstream(line);
				line_s >> vertex.x >> vertex.y >> vertex.z;
				Vertex newVertex(vertices.size(), vertex);

				vertices.push_back(newVertex);
			}
			if (line.substr(0, line.find(' ')) == "vt") {
				line.erase(0, 2);
				glm::vec2 uv;
				stringstream line_s = stringstream(line);
				line_s >> uv.x >> uv.y;

				tex_coords.push_back(uv);
			}
			if (line.substr(0, line.find(' ')) == "vn") {
				line.erase(0, 2);
				glm::vec3 vertex;
				stringstream line_s = stringstream(line);
				line_s >> vertex.x >> vertex.y >> vertex.z;

				normals.push_back(vertex);
			}
			if (line.substr(0, line.find(' ')) == "f") {
				line.erase(0, 1);
				stringstream line_s = stringstream(line);
				std::string vertex1;
				std::string vertex2;
				std::string vertex3;
				line_s >> vertex1 >> vertex2 >> vertex3;

				processVertex(vertex1, vertices, indices);
				processVertex(vertex2, vertices, indices);
				processVertex(vertex3, vertices, indices);

			}


		}



	}

	removeUnusedVertices(vertices);

	float *verticesArray = new float[vertices.size() * 3];
	float *textureArray = new float[vertices.size() * 2];
	float *normalArray = new float[vertices.size() * 3];

	convertDataToArrays(vertices, tex_coords, normals, verticesArray, textureArray, normalArray, out_vertices, out_indices, out_uvs, out_normals);


	out_indices = indices;

	int* indicesArray = &indices[0];


	file.close();
	return { out_vertices,out_uvs,out_normals,out_indices };
}

float OBJLoader::convertDataToArrays(std::vector<Vertex> &vertices, std::vector<glm::vec2> &textures,
	std::vector<glm::vec3> &normals, float *verticesArray, float *texturesArray,
	float *normalsArray, std::vector<float> &out_vertices,
	std::vector<int> &out_indices,
	std::vector<float> &out_uvs,
	std::vector<float> & out_normals) {


	float furthestPoint = 0;
	for (int i = 0; i < vertices.size(); i++) {
		Vertex currentVertex = vertices[i];
		if (currentVertex.getLength() > furthestPoint) {
			furthestPoint = currentVertex.getLength();
		}
		glm::vec3 position = currentVertex.getPosition();
		glm::vec2 textureCoord = textures[currentVertex.getTextureIndex()];
		glm::vec3 normalVector = normals[currentVertex.getNormalIndex()];
		verticesArray[i * 3] = position.x;
		verticesArray[i * 3 + 1] = position.y;
		verticesArray[i * 3 + 2] = position.z;

		out_vertices.push_back(position.x);
		out_vertices.push_back(position.y);
		out_vertices.push_back(position.z);



		texturesArray[i * 2] = textureCoord.x;
		texturesArray[i * 2 + 1] = 1.0f - textureCoord.y;

		out_uvs.push_back(textureCoord.x);
		out_uvs.push_back(textureCoord.y);


		normalsArray[i * 3] = normalVector.x;
		normalsArray[i * 3 + 1] = normalVector.y;
		normalsArray[i * 3 + 2] = normalVector.z;

		out_normals.push_back(normalVector.x);
		out_normals.push_back(normalVector.y);
		out_normals.push_back(normalVector.z);


	}
	return furthestPoint;
}



void OBJLoader::removeUnusedVertices(std::vector<Vertex> &vertices) {
	for (int i = 0; i < vertices.size(); i++) {
		if (!vertices[i].isSet()) {
			vertices[i].setTextureIndex(0);
			vertices[i].setNormalIndex(0);
		}
	}
}
template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}
std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}
void OBJLoader::processVertex(std::string vertex, std::vector<Vertex> &vertices, std::vector<int> &indices) {
	int index;
	int textureIndex;
	int normalIndex;


	char h = '/';
	index = atoi(split(vertex, h)[0].c_str()) - 1;
	textureIndex = atoi(split(vertex, h)[1].c_str()) - 1;
	normalIndex = atoi(split(vertex, h)[2].c_str()) - 1;

	Vertex currentVertex = vertices[index];
	if (!vertices[index].isSet()) {
		vertices[index].setTextureIndex(textureIndex);
		vertices[index].setNormalIndex(normalIndex);
		indices.push_back(index);

	}

	else {

		dealWithAlreadyProcessedVertex(vertices[index], textureIndex, normalIndex, indices,
			vertices);



	}

}
void OBJLoader::dealWithAlreadyProcessedVertex(Vertex &previousVertex, int newTextureIndex,
	int newNormalIndex, std::vector<int> &indices, std::vector<Vertex> &vertices) {

	if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
		indices.push_back(previousVertex.getIndex());

	}
	else {
		if (previousVertex.getDuplicateVertex() != nullptr) {

			dealWithAlreadyProcessedVertex(*previousVertex.getDuplicateVertex(), newTextureIndex, newNormalIndex,
				indices, vertices);
		}
		else {
			Vertex *duplicateVertex = new Vertex(vertices.size(), previousVertex.getPosition());
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);
			previousVertex.setDuplicateVertex(duplicateVertex);
			vertices.push_back(*duplicateVertex);
			indices.push_back(duplicateVertex->getIndex());
		}

	}

}
ModelData *OBJLoader::loadOBJp(const char* path) {

	std::vector<Vertex> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> tex_coords;
	std::vector<int> indices;

	std::vector<float> out_vertices;
	std::vector<int> out_indices;
	std::vector<float> out_uvs;
	std::vector<float> out_normals;

	ifstream file;
	file.open(path);
	string output;
	if (file.is_open()) {

		std::string line;

		while (getline(file, line)) {

			if (line.substr(0, line.find(' ')) == "v") {

				line.erase(0, 1);
				glm::vec3 vertex;
				stringstream line_s = stringstream(line);
				line_s >> vertex.x >> vertex.y >> vertex.z;
				Vertex newVertex(vertices.size(), vertex);

				vertices.push_back(newVertex);
			}
			if (line.substr(0, line.find(' ')) == "vt") {
				line.erase(0, 2);
				glm::vec2 uv;
				stringstream line_s = stringstream(line);
				line_s >> uv.x >> uv.y;

				tex_coords.push_back(uv);
			}
			if (line.substr(0, line.find(' ')) == "vn") {
				line.erase(0, 2);
				glm::vec3 vertex;
				stringstream line_s = stringstream(line);
				line_s >> vertex.x >> vertex.y >> vertex.z;

				normals.push_back(vertex);
			}
			if (line.substr(0, line.find(' ')) == "f") {
				line.erase(0, 1);
				stringstream line_s = stringstream(line);
				std::string vertex1;
				std::string vertex2;
				std::string vertex3;
				line_s >> vertex1 >> vertex2 >> vertex3;

				processVertex(vertex1, vertices, indices);
				processVertex(vertex2, vertices, indices);
				processVertex(vertex3, vertices, indices);

			}


		}



	}

	removeUnusedVertices(vertices);

	float *verticesArray = new float[vertices.size() * 3];
	float *textureArray = new float[vertices.size() * 2];
	float *normalArray = new float[vertices.size() * 3];

	convertDataToArrays(vertices, tex_coords, normals, verticesArray, textureArray, normalArray, out_vertices, out_indices, out_uvs, out_normals);


	out_indices = indices;

	int* indicesArray = &indices[0];


	file.close();
	return new ModelData{ out_vertices, out_uvs, out_normals, out_indices };
}