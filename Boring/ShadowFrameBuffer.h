#pragma once
#include <GL\glew.h>

class ShadowFrameBuffer
{
public:
	ShadowFrameBuffer();
	GLuint frameBuffer;
	GLuint depthMap;
	GLuint createFrameBuffer();
	void unBindCurrentFrameBuffer();
	void cleanUp();
	void bindFrameBuffer();
	~ShadowFrameBuffer();
private:
	void bindFrameBuffer(GLuint frameBuffer, int width, int height);
	GLuint createDepthBufferAttachment(int width, int height);

};

