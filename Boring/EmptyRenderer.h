#pragma once
#include "Shader.h"
#include "FrameBuffer.h"
#include "OBJLoader.h"
#include "DataTypes.h"
#include "Texture.h"
#include "EntityHandler.h"

class EmptyRendererComponent : public Component<EmptyRendererComponent>
{

public:
	EmptyRendererComponent() {}
	EmptyRendererComponent(const char* path);
	void render(GLuint texture);
	FrameBuffer fbo;
	void setUniform(const char * location, int value);
	void setUniform(const char * location, float value);
	void setTextureUniform(const char *location, Texture &texture, int position);
	GLuint v;

private:
	//int
	vector<int> integers;
	vector<const char *> intloc;
	//float
	vector<float> floats;
	vector<const char *> floatloc;
	//texture
	vector<Texture *> textures;
	vector<int> positions;
	vector<float> vertices;

	Shader shader;

};
class EmptyRenderer : public Component<EmptyRenderer>
{

public:
	EmptyRenderer() {}
	EmptyRenderer(const char* path);
	void render(GLuint texture);
	FrameBuffer fbo;
	void setUniform(const char * location, int value);
	void setUniform(const char * location, float value);
	void setTextureUniform(const char *location, Texture &texture, int position);
	GLuint v;

private:
	//int
	vector<int> integers;
	vector<const char *> intloc;
	//float
	vector<float> floats;
	vector<const char *> floatloc;
	//texture
	vector<Texture *> textures;
	vector<int> positions;
	vector<float> vertices;

	Shader shader;

};
