#pragma once
#include "system.h"
#include "FrameBuffer.h"
#include "Shader.h"
#include "EmptyRenderer.h"
#include "CombineFilter.h"
#include "State.h"

class PostRenderSystem : public System
{
public:
	PostRenderSystem();
	void update(double delta);
	~PostRenderSystem();
private:
	vector<float> vertices = { -1,1,1,1,-1,-1, //first triangle
		1,1,1,-1,-1,-1 //second triangle
	};
	GLuint vao;
	FrameBuffer outFbo;
	FrameBuffer bloomFbo;
	Shader shader;
	EmptyRenderer *verticalBlur;
	EmptyRenderer *horizontalBlur;
	CombineFilter *combine;
};

