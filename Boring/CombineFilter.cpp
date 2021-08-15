#include "CombineFilter.h"
#include "State.h"


CombineFilter::CombineFilter(const char *path) {
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

void CombineFilter::render(GLuint texture0, GLuint texture1) {
	fbo.bindFrameBuffer();
	shader.bind();
	shader.setUniform("colourTexture", 0);
	shader.setUniform("highlightTexture", 1);
	glBindVertexArray(v);
	glEnableVertexAttribArray(0);



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);


	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.unBind();
	fbo.unBindFrameBuffer();
}