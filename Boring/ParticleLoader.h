#pragma once
#include <fstream>
#include <iostream>
#include "ParticleRenderer.h"

using namespace std;

class ParticleLoader
{
public:
	ParticleLoader();
	static int loadParticle(const char* path,EntityHandler &handler);
	~ParticleLoader();
private:
	static ModelData* loadMesh();
	static ifstream file;
};

