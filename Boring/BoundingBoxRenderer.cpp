#include "BoundingBoxRenderer.h"
#include "Maths.h"


BoundingBoxRenderer::BoundingBoxRenderer()
{
	shader = Shader("shaders/bounding");
	OBB o;

	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	vector<float> data = {
			1,1,1,
			-1,1,1,
			1,1,1,
			1,-1,1,
			1,1,1,
			1,1,-1,

			-1,-1,-1,
			1,-1,-1,
			-1,-1,-1,
			-1,1,-1,
			-1,-1,-1,
			-1,-1,1,

			-1,1,1,
			-1,1,-1,
			1,-1,1,
			-1,-1,1,
			1,1,-1,
			-1,1,-1,
			
			1,1,-1,
			1,-1,-1,

			1,-1,1,
			1,-1,-1,

			-1,1,1,
			-1,-1,1

	};
	

	GLuint v_vbo;
	glGenBuffers(1, &v_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*data.size(), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}
void BoundingBoxRenderer::updateComponents(double delta)
{
	
}
void BoundingBoxRenderer::updateSystem(double delta)
{
	shader.bind();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	vector<OBB> models = getComponents<OBB>();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	mat4x4 projection = functions::createProjectionMatrix(70, .1, 1000);
	shader.setUniform("view", functions::createViewMatrix(State::camera));
	shader.setUniform("projection", projection);
	for (int i = 0; i < models.size(); i++) {
		shader.setUniform("color", models[i].color);
		shader.setUniform("offset", models[i].offset);
		shader.setUniform("transformation", functions::createTransformationMatrix(models[i].position, models[i].rotation, models[i].scale));
		glDrawArrays(GL_LINES, 0, 36);
	}
	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	shader.unBind();
}
BoundingBoxRenderer::~BoundingBoxRenderer()
{
}
