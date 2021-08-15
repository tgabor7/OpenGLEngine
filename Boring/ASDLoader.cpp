#include "ASDLoader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <glm\mat4x4.hpp>
#include "Quaternion.h"

using namespace glm;
using namespace std;

ASDLoader::ASDLoader()
{
}
ModelData ASDLoader::loadSkin(const char* path) {

	ifstream file(path, ios::in | ios::binary);
	char *i = new char[4];
	file.read(i, 4);

	file.read(i, 4);
	uint32_t size = 0;
	memcpy(&size, i, sizeof(uint32_t));
	size *= 3 * 8;


	vector<float> vertices;
	vector<float> tex_coords;
	vector<float> normals;
	vector<int> indices;
	char *d = new char[8];
	double k;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		vertices.push_back(k);

	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 3;
	int z;
	for (int i = 0; i < size; i++) {
		file.read(d, 4);
		memcpy(&z, d, sizeof(int));
		indices.push_back(z);
	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 3 * 8;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		normals.push_back(k);

	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 8;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		tex_coords.push_back(k);

	}
	for (int i = 0; i < indices.size(); i++) {
		indices[i] = i;
	}
	vector<float> convertedTexCoords(tex_coords.size());
	for (int i = 0; i < tex_coords.size() / 2; i++) {
		convertedTexCoords[i * 2] = tex_coords[i * 2];
		convertedTexCoords[i * 2 + 1] = 1 - tex_coords[i * 2 + 1];

	}
	ModelData data({ vertices, convertedTexCoords, normals, indices });
	return data;
}
Animation ASDLoader::loadAnimation(const char* path) {
	ifstream file(path, ios::in | ios::binary);
	int r;

	char *i = new char[4];
	file.read(i, 4);
	memcpy(&r, i, sizeof(int));
	r += 1;
	file.read(i, 4);
	uint32_t size = 0;
	memcpy(&size, i, sizeof(uint32_t));
	size *= 3 * 8;


	vector<float> vertices;
	vector<float> tex_coords;
	vector<float> normals;
	vector<int> indices;
	vector<int> temp_indices;
	vector<mat4x4> bindMatrix;

	char *d = new char[8];
	double k;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		vertices.push_back(k);

	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 3;
	int z;
	for (int i = 0; i < size; i++) {
		file.read(d, 4);
		memcpy(&z, d, sizeof(int));
		indices.push_back(z);
	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 3 * 8;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		normals.push_back(k);

	}
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	size *= 8;
	for (int i = 0; i < size / 8; i++) {
		file.read(d, 8);
		memcpy(&k, d, sizeof(double));
		tex_coords.push_back(k);

	}
	temp_indices = indices;
	for (int i = 0; i < indices.size(); i++) {
		indices[i] = i;

	}
	vector<float> convertedTexCoords(tex_coords.size());
	for (int i = 0; i < tex_coords.size() / 2; i++) {
		convertedTexCoords[i * 2] = tex_coords[i * 2];
		convertedTexCoords[i * 2 + 1] = 1 - tex_coords[i * 2 + 1];

	}
	int bSize;
	file.read(i, 4);
	memcpy(&bSize, i, sizeof(int));
	for (int i = 0; i < bSize; i++) {
		vector<float> bindM;

		for (int j = 0; j < 16; j++) {
			file.read(d, 8);
			memcpy(&k, d, sizeof(double));
			bindM.push_back(k);

		}
		bindMatrix.push_back(mat4x4(
			bindM[0], bindM[1], bindM[2], bindM[3],
			bindM[4], bindM[5], bindM[6], bindM[7],
			bindM[8], bindM[9], bindM[10], bindM[11],
			bindM[12], bindM[13], bindM[14], bindM[15]

		));

	}
	vector<KeyFrame> frames;
	vector<Bone> tmpBones;
	vector<Bone> bones;
	for (int i = 0; i < bSize; i++) {

		for (int j = 0; j < r; j++) {
			vec3 pos;
			file.read(d, 8);
			memcpy(&k, d, 8);
			pos.x = k;

			file.read(d, 8);
			memcpy(&k, d, 8);
			pos.y = k;

			file.read(d, 8);
			memcpy(&k, d, 8);
			pos.z = k;



			file.read(d, 8);
			memcpy(&k, d, 8);
			float w = k;

			file.read(d, 8);
			memcpy(&k, d, 8);
			float x = k;

			file.read(d, 8);
			memcpy(&k, d, 8);
			float y = k;

			file.read(d, 8);
			memcpy(&k, d, 8);
			float z = k;
			Quaternion q(x, y, z, w);

			Bone b{ pos,q,"",bindMatrix[i] };
			tmpBones.push_back(b);
		}


	}

	for (int i = 0; i < tmpBones.size() / bSize; i++) {
		vector<Bone> bs;
		for (int j = 0; j < bSize; j++) {
			bs.push_back(tmpBones[i + (tmpBones.size() / bSize)*j]);
		}


		frames.push_back(KeyFrame{ bs });
	}
	vector<int> jointIndices;
	vector<float> weights;


	for (int w = 0; w < indices.size() * 4; w++)
	{
		double j;
		file.read(i, 8);
		memcpy(&j, i, 8);
		jointIndices.push_back(j);
	}

	for (int w = 0; w < indices.size() * 4; w++)
	{
		if (file && file.peek() == EOF) {
			cout << "File load failed." << endl;
		}
		double l;
		file.read(d, 8);
		memcpy(&l, d, 8);
		weights.push_back(l);
	}
	vector<int> converted_jointIndices(indices.size() * 4);
	vector<float> converted_weights(indices.size() * 4);

	for (int i = 0; i < indices.size(); i++) {
		converted_jointIndices[i * 4] = jointIndices[temp_indices[i] * 4];
		converted_jointIndices[i * 4 + 1] = jointIndices[temp_indices[i] * 4 + 1];
		converted_jointIndices[i * 4 + 2] = jointIndices[temp_indices[i] * 4 + 2];
		converted_jointIndices[i * 4 + 3] = jointIndices[temp_indices[i] * 4 + 3];

	}

	for (int i = 0; i < indices.size(); i++) {
		converted_weights[i * 4] = weights[temp_indices[i] * 4];
		converted_weights[i * 4 + 1] = weights[temp_indices[i] * 4 + 1];
		converted_weights[i * 4 + 2] = weights[temp_indices[i] * 4 + 2];
		converted_weights[i * 4 + 3] = weights[temp_indices[i] * 4 + 3];

	}

	Animation animation(jointIndices, weights, frames);

	return animation;
}
ASDLoader::~ASDLoader()
{
}
