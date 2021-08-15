#pragma once

#include "Mesh.h"
#include "system.h"
#include "EntityHandler.h"
#include "Shader.h"
#include "Maths.h"

struct MeshInstance
{
	vec3 position;
	vec3 rotation;
	vec3 scale;
	Texture *texture;
};
class InstanceComponent : public Component<InstanceComponent>
{
public:
	InstanceComponent() {}
	InstanceComponent(ModelData data);
	InstanceComponent(ModelData data,bool rot);
	vector<MeshInstance> meshes;
	vector<Texture*> textures;
	ModelData data;
	int draw_count;
	GLuint vao;
	GLuint vbo;
	void addInstance(vec3 position, vec3 rotation, vec3 scale, Texture *texture);
	void addInstance(MeshInstance instance);
	void removeInstance(int id);
	bool rotation;
	~InstanceComponent() {}
private:

};

class InstanceRenderSystem : public System
{
public:
	InstanceRenderSystem();
	void update(double delta);
	~InstanceRenderSystem();
private:
	Shader shader;
	vector<float> vboData;
	int pointer = 0;
	void storeMatrixData(mat4x4 matrix, float * vboData);
	void bindTexture(Texture *texture);
	void updateModelViewMatrix(vec3 position, float rx, float ry, float rz, float width, float height, float length, float scale, float * vboData);
};

