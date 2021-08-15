#include "FrameBuffer.h"

#include "PostRenderSystem.h"
#include "EmptyRenderer.h"

PostRenderSystem::PostRenderSystem()
{
	shader = Shader("shaders/post");
	verticalBlur = new EmptyRenderer("shaders/Vblur");
	horizontalBlur = new EmptyRenderer("shaders/Hblur");
	switch (State::BLOOM_SIZE) {
	case(SMALL):
		verticalBlur->setUniform("targetHeight", (float)State::HEIGHT);
		horizontalBlur->setUniform("targetWidth", (float)State::WIDTH);
		break;
	case(MEDIUM):
		verticalBlur->setUniform("targetHeight", (float)State::HEIGHT / 5);
		horizontalBlur->setUniform("targetWidth", (float)State::WIDTH / 5);
		break;
	case(LARGE):
		verticalBlur->setUniform("targetHeight", (float)State::HEIGHT / 10);
		horizontalBlur->setUniform("targetWidth", (float)State::WIDTH / 10);
		break;
	}

	combine = new CombineFilter("shaders/combine");
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	outFbo = FrameBuffer(State::WIDTH, State::HEIGHT, FrameBuffer::DEPTH_TEXTURE);
	bloomFbo = FrameBuffer(State::WIDTH, State::HEIGHT, FrameBuffer::DEPTH_TEXTURE);

}
void PostRenderSystem::update(double delta)
{
	vector<EmptyRendererComponent> filters = getComponents<EmptyRendererComponent>();


	State::fbo->resolveFbo(GL_COLOR_ATTACHMENT0, outFbo);
	State::fbo->resolveFbo(GL_COLOR_ATTACHMENT2, bloomFbo);

	verticalBlur->render(bloomFbo.colorTexture);
	horizontalBlur->render(verticalBlur->fbo.colorTexture);


	if (filters.size() > 0) {
		combine->render(horizontalBlur->fbo.colorTexture, outFbo.colorTexture);
		filters[0].render(combine->fbo.colorTexture);
		for (int i = 1; i < filters.size(); i++) {
			filters[i].render(filters[i - 1].fbo.colorTexture);
		}
	}

	shader.bind();
	shader.setUniform("sampler", 0);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);
	if (filters.size() > 0) glBindTexture(GL_TEXTURE_2D, filters[filters.size() - 1].fbo.colorTexture);
	else glBindTexture(GL_TEXTURE_2D, outFbo.colorTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unBind();
}

PostRenderSystem::~PostRenderSystem()
{
}
