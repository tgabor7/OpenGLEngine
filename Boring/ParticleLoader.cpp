#include "ParticleLoader.h"


ifstream ParticleLoader::file;

ParticleLoader::ParticleLoader()
{

}
int ParticleLoader::loadParticle(const char* path,EntityHandler &handler)
{
	file.open(path, ios::in | ios::binary);

	ModelData *data = loadMesh();

	ParticleSystem *p = new ParticleSystem(new Texture("res/gray.png"));
	ParticleRenderer *r = new ParticleRenderer(data);
	return handler.makeEntity(*p,*r);
}

ModelData* ParticleLoader::loadMesh()
{
	char *d = new char[8];
	char *i = new char[4];
	int size;
	vector<float> vertices;
	vector<float> textures;
	vector<float> normals;
	vector<int> indices;

	//vertices
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	for (int j = 0; j < size; ++j) {
		float f;
		file.read(i, 4);
		memcpy(&f, i, sizeof(float));
		vertices.push_back(f);
	}

	//textures
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	for (int j = 0; j < size; ++j) {
		float f;
		file.read(i, 4);
		memcpy(&f, i, sizeof(float));
		textures.push_back(f);
	}

	//normals
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	for (int j = 0; j < size; ++j) {
		float f;
		file.read(i, 4);
		memcpy(&f, i, sizeof(float));
		normals.push_back(f);
	}
	//indices
	file.read(i, 4);
	memcpy(&size, i, sizeof(int));
	for (int j = 0; j < size; ++j) {
		int f;
		file.read(i, 4);
		memcpy(&f, i, sizeof(int));
		indices.push_back(f);
	}
	file.close();

	ModelData *data = new ModelData{ vertices,textures,normals,indices };
	return data;
}

ParticleLoader::~ParticleLoader()
{
}
