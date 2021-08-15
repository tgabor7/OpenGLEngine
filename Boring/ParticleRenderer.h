#pragma once
#include <vector>
#include "Loader.h"

#include "DataTypes.h"
#include "Maths.h"

#include "ParticleShader.h"

#include "ParticleSystem.h"


using namespace std;

class ParticleRenderer : public Component<ParticleRenderer>
{
public:
	float verts[12] = {
		-1,-1,
		-1,1,
		1,-1,
		1,1,
		1,-1,
		-1,1 };
	float textures[8] = { 0.0,0.0,
		1.0,0.0,
		1.0,1.0,
		0.0,1.0 };

	//rendering stuff

	GLuint program;
	GLuint vao;
	GLuint vertexposvbo;
	GLuint indexvbo;
	GLuint vbo;
	GLuint svbo;
	GLuint rvbo;
	GLuint lifevbo;
	GLuint locVertexPos;
	float* pVertexPosBufferData;
	float *pVertexPosCurrent;
	float* pIndexBuffer;
	size_t bufferDataIndex;

	ParticleShader *shader;

	int draw_count;
	vector<float> vboData;
	vector<float> svbodata;
	vector<float> rvbodata;
	vector<float> lifedata;

	mat4 projection;
	mat4 view;

	float billboard;
	Texture *tex;
	ParticleRenderer(ModelData* data);
	ParticleRenderer() {}
	void render(ParticleSystem *ps, Camera c);
	void rebind(ModelData *data);
	~ParticleRenderer();
};

