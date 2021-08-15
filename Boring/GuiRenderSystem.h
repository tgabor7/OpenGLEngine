#pragma once
#include "System.h"
#include "Shader.h"
#include "Maths.h"
#include "OBJLoader.h"
#include "Loader.h"
#include "Texture.h"

using namespace glm;

class GUIComponent : public Component<GUIComponent>
{
public:
	GUIComponent() {}
	GUIComponent(Texture *texture) {
		this->texture = texture;
		this->scale = vec2(100);
	}
	vec2 position;
	vec2 scale;
	float roatation;
	Texture *texture;
private:

};

class GuiRenderSystem : public System 
{
public:
	GuiRenderSystem();
	void updateComponents(double delta);
	void updateSystem(double delta);
	~GuiRenderSystem();
private:
	int draw_count;
	int pointer;
	vector<float> vboData;
	GLuint vbo;
	Shader shader;
	GLuint vao;
	mat4x4 projection;
	void storeMatrixData(mat4x4 matrix, float * vboData);
	void bindTexture(Texture *texture);
	void updateModelViewMatrix(vec3 position, float rx, float ry, float rz, float width, float height, float length, float scale, float * vboData);
};

