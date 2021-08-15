#pragma once
#include "System.h"
#include "Shader.h"
#include "SAT.h"

class BoundingBoxRenderer : public System
{
public:
	BoundingBoxRenderer();
	void updateComponents(double delta);
	void updateSystem(double delta);
	~BoundingBoxRenderer();
private:
	GLuint vao;
	GLuint vbo;
	Shader shader;
	int draw_count;
};

