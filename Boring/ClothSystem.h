#pragma once
#include "System.h"
#include "Loader.h"
#include "OBJLoader.h"
#include "EmptyRenderer.h"
#include "Maths.h"

class ClothSystem : public System
{
public:
	ClothSystem();
	void updateComponents(double delta);
	void updateSystem(double delta);
	~ClothSystem();
private:
	GLuint vao;
	GLuint vbo;
	ModelData data;
	float* vertices;
	Shader *shader;
	mat4x4 transformation;
	mat4x4 projection;
};

