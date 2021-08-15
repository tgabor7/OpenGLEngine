#include "EmptyRenderer.h"
#include "State.h"


EmptyRenderer::EmptyRenderer(const char *path) {
	shader = Shader(path);

	vertices = { -1,1,1,1,-1,-1, //first triangle
		1,1,1,-1,-1,-1 //second triangle
	};

	glGenVertexArrays(1, &v);
	glBindVertexArray(v);
	glEnableVertexAttribArray(0);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
	glDisableVertexAttribArray(0);

	switch (State::BLOOM_SIZE) {
	case(SMALL):
		fbo = FrameBuffer(State::WIDTH, State::HEIGHT, FrameBuffer::DEPTH_RENDER_BUFFER);
		break;
	case(MEDIUM):
		fbo = FrameBuffer(State::WIDTH / 5, State::HEIGHT / 5, FrameBuffer::DEPTH_RENDER_BUFFER);
		break;
	case(LARGE):
		fbo = FrameBuffer(State::WIDTH / 10, State::HEIGHT / 10, FrameBuffer::DEPTH_RENDER_BUFFER);
		break;
	}

}
float t = -1.f;
void EmptyRenderer::render(GLuint texture) {
	fbo.bindFrameBuffer();
	shader.bind();
	shader.setUniform("sampler", 0);
	shader.setUniform("width", State::WIDTH);
	shader.setUniform("height", State::HEIGHT);
	glBindVertexArray(v);
	glEnableVertexAttribArray(0);


	for (int i = 0; i < integers.size(); i++) {
		shader.setUniform(intloc[i], integers[i]);
	}
	for (int i = 0; i < floats.size(); i++) {
		shader.setUniform(floatloc[i], floats[i]);
	}
	for (int i = 0; i < positions.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + positions[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]->texture_id);

	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unBind();
	fbo.unBindFrameBuffer();
}
void EmptyRenderer::setUniform(const char * location, int value) {


	intloc.push_back(location);
	integers.push_back(value);


}
void EmptyRenderer::setUniform(const char * location, float value) {

	floatloc.push_back(location);
	floats.push_back(value);

}
void EmptyRenderer::setTextureUniform(const char *location, Texture &tex, int position) {

	this->setUniform(location, position);
	textures.push_back(&tex);
	positions.push_back(position);

}
EmptyRendererComponent::EmptyRendererComponent(const char *path) {
	shader = Shader(path);

	vertices = { -1,1,1,1,-1,-1, //first triangle
		1,1,1,-1,-1,-1 //second triangle
	};

	glGenVertexArrays(1, &v);
	glBindVertexArray(v);
	glEnableVertexAttribArray(0);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);
	glDisableVertexAttribArray(0);


	fbo = FrameBuffer(State::WIDTH, State::HEIGHT, FrameBuffer::DEPTH_RENDER_BUFFER);
}

void EmptyRendererComponent::render(GLuint texture) {
	fbo.bindFrameBuffer();
	shader.bind();
	shader.setUniform("sampler", 0);
	shader.setUniform("width", State::WIDTH);
	shader.setUniform("height", State::HEIGHT);
	glBindVertexArray(v);
	glEnableVertexAttribArray(0);


	for (int i = 0; i < integers.size(); i++) {
		shader.setUniform(intloc[i], integers[i]);
	}
	for (int i = 0; i < floats.size(); i++) {
		shader.setUniform(floatloc[i], floats[i]);
	}
	for (int i = 0; i < positions.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + positions[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i]->texture_id);

	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unBind();
	fbo.unBindFrameBuffer();
}
void EmptyRendererComponent::setUniform(const char * location, int value) {


	intloc.push_back(location);
	integers.push_back(value);


}
void EmptyRendererComponent::setUniform(const char * location, float value) {

	floatloc.push_back(location);
	floats.push_back(value);

}
void EmptyRendererComponent::setTextureUniform(const char *location, Texture &tex, int position) {

	this->setUniform(location, position);
	textures.push_back(&tex);
	positions.push_back(position);

}