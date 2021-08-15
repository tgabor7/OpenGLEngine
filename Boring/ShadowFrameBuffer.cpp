#include "ShadowFrameBuffer.h"
#include "State.h"

static int WIDTH = 1024 * 4;
static int HEIGHT = 1024 * 4;

ShadowFrameBuffer::ShadowFrameBuffer()
{
	frameBuffer = createFrameBuffer();
	depthMap = createDepthBufferAttachment(WIDTH, HEIGHT);
	unBindCurrentFrameBuffer();
}

GLuint ShadowFrameBuffer::createFrameBuffer() {
	GLuint frameBuffer;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_NONE);
	return frameBuffer;
}
void ShadowFrameBuffer::bindFrameBuffer(GLuint frameBuffer, int width, int height) {
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}
void ShadowFrameBuffer::bindFrameBuffer() {
	bindFrameBuffer(frameBuffer, WIDTH, HEIGHT);
}
GLuint ShadowFrameBuffer::createDepthBufferAttachment(int width, int height) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, (void*)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	const float borderColor[] = { 1, 1, 1, 1 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
		borderColor);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);

	return texture;
}
void ShadowFrameBuffer::unBindCurrentFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, State::WIDTH, State::HEIGHT);
}
void ShadowFrameBuffer::cleanUp() {
	glDeleteFramebuffers(1, &frameBuffer);

}
ShadowFrameBuffer::~ShadowFrameBuffer()
{
}
