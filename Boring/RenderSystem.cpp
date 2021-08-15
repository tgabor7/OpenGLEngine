#include "RenderSystem.h"
#include "ParticleRenderer.h"

vector<CustomRenderSystem*> RenderSystem::custom_renderer;
RenderSystem::RenderSystem()
{
	shader = Shader("shaders/shader");
	background_shader = Shader("shaders/background");
	shadow_shader = Shader("shaders/shadowshader");
	billboard_shader = Shader("shaders/billboard");
	anim_shadow_shader = AnimatedShader("shaders/animatedshadow");
	texture = new Texture("res/gray.png");
	cloth_renderer = ClothSystem();

	for (int i = 0; i < 4; i++) {
		fbos.push_back(ShadowFrameBuffer());
	}

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

}
void RenderSystem::updateComponents(double delta)
{
	//Mesh *m = (Mesh*)getComponent(Mesh::type)[0];
	
}
void RenderSystem::updateSystem(double delta)
{
	vector<Mesh> models = getComponents<Mesh>();
	vector<Light> lights = getComponents<Light>();
	vector<BillBoard> billboards = getComponents<BillBoard>();
	vector<AnimatedMesh> animes = getComponents<AnimatedMesh>();
	vector<BaseComponent*> particles = getComponents(ParticleSystem::type);
	vector<BaseComponent*> pRenderers = getComponents(ParticleRenderer::type);
	
	renderShadow(models, lights);
	renderShadow(animes, lights);
	State::fbo->bindFrameBuffer();
	
	mat4x4 projection = functions::createProjectionMatrix(70,.1,1000);
	mat4x4 view = functions::createViewMatrix(State::camera);
	
	glDisable(GL_DEPTH_TEST);
	drawBackground();
	
	glEnable(GL_DEPTH_TEST);

	shader.bind();
	mat4x4 lightSpaces[4];
	for (int i = 0; i < lights.size(); i++) {
		mat4x4 projection = glm::ortho(-500.f, 500.f, -500.f, 500.f, -250.f, 2000.f);
		mat4x4 view = glm::lookAt(lights[i].position, vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
		mat4x4 lightSpace = projection * view;
		glm::translate(lightSpace, State::camera.pointToLookAt);
		lightSpaces[i] = lightSpace;
	}
	shader.setUniform("lightSpaceMatrix", lightSpaces);
	shader.setUniform("shadowMap[0]", 1);
	shader.setUniform("shadowMap[1]", 3);
	shader.setUniform("shadowMap[2]", 4);
	shader.setUniform("shadowMap[3]", 5);
	shader.setUniform("specularMap", 2);
	shader.setUniform("distMap", 6);
	shader.setUniform("projection", projection);
	shader.setUniform("view", view);
	vec3 lightp[4];
	for (int i = 0; i < lights.size(); i++) {
		lightp[i] = lights[i].position;
	}
	shader.setUniform("lightPosition", lightp);
	vec3 lightc[4];

	for (int i = 0; i < lights.size(); i++) {
		lightc[i] = lights[i].color;
	}
	shader.setUniform("lightColor", lightc);
	glm::vec3 att[4];
	for (int i = 0; i < lights.size(); i++) {
		att[i] = lights[i].attenuation;
	}
	shader.setUniform("attenuation", att);

	shader.setUniform("numberOfLights", (int)lights.size());
	for (int i = 0; i < models.size(); i++) {
		setupTexture(&models[i].texture->texture_id);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, models[i].texture->speculatTexture);

		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, models[i].texture->bloomMap);

		shader.setUniform("transformation", functions::createTransformationMatrix(models[i].position,models[i].rotation,models[i].scale));
		shader.setUniform("customColor", models[i].color);
		shader.setUniform("rows", 1);
		shader.setUniform("columns", 1);
		shader.setUniform("pointer", 1);
		shader.setUniform("reflectivity", 0.5f);
		shader.setUniform("shineDamper", 0.999f);
		shader.setUniform("outLineColor", vec4(0, 0, 0, 0));
		shader.setUniform("useFakeLightning", 0);
		shader.setUniform("usesSpecularMap", 0);
		shader.setUniform("usesDistMap", 0);
		shader.setUniform("useFakeLightning", 0.f);



		glBindVertexArray(models[i].vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glDrawElements(GL_TRIANGLES, models[i].draw_count, GL_UNSIGNED_INT, 0);
		if (models[i].outLineColor.a > 0) {
			
			shader.setUniform("transformation", functions::createTransformationMatrix(models[i].position, models[i].rotation, models[i].scale+(.0003f*State::camera.distance)));
			shader.setUniform("customColor", models[i].outLineColor);
			shader.setUniform("useFakeLightning", 1.0f);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glBindVertexArray(models[i].vao);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, models[i].draw_count, GL_UNSIGNED_INT, 0);

			glDisable(GL_CULL_FACE);
		}
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}
	
		
	shader.unBind();
	
	for (int i = 0; i < particles.size(); i++) {
		ParticleRenderer* pr = (ParticleRenderer*)pRenderers[i];
		pr->render((ParticleSystem*)particles[i], State::camera);
	}
	
	renderBillBoards(billboards);
	instanceRenderer.update(delta);
	animationRenderer.render(animes, lights, fbos);
	cloth_renderer.update(delta);

	for (int i = 0; i < custom_renderer.size(); i++) {
		custom_renderer[i]->render();
	}
	State::fbo->unBindFrameBuffer();
}
void RenderSystem::drawBackground()
{
	background_shader.bind();
	background_shader.setUniform("sampler", 0);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texture->texture_id);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	background_shader.unBind();
}
void RenderSystem::setupTexture(GLuint *texture)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);

	if (fbos.size() > 0) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, fbos[0].depthMap);

	}
	for (int i = 1; i < fbos.size(); i++) {

		glActiveTexture(GL_TEXTURE3 + i - 1);
		glBindTexture(GL_TEXTURE_2D, fbos[i].depthMap);

	}
}
void RenderSystem::renderShadow(std::vector<Mesh> models,std::vector<Light> lights)
{
	for (int i = 0; i < lights.size(); i++) {
		fbos[i].bindFrameBuffer();
		glClearColor(.3f, .3f, .3f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadow_shader.bind();
		mat4x4 lightSpaces[4];
		mat4x4 projection = glm::ortho(-500.f, 500.f, -500.f, 500.f, -250.f, 2000.f);
		mat4x4 view = glm::lookAt(lights[i].position, vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
		mat4x4 lightSpace = projection * view;
		glm::translate(lightSpace, State::camera.pointToLookAt);
		lightSpaces[0] = lightSpace;

		shadow_shader.setUniform("lightSpaceMatrix", lightSpace);

		for (int i = 0; i < models.size(); i++) {
			if (!models[i].has_shadow) break;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, models[i].texture->texture_id);

			glBindVertexArray(models[i].vao);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);


			shadow_shader.setUniform("shadowMap", 0);
			shadow_shader.setUniform("model", functions::createTransformationMatrix(models[i].position, models[i].rotation, models[i].scale));


			glDrawElements(GL_TRIANGLES, (GLsizei)models[i].draw_count, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
		}
		shadow_shader.unBind();
		fbos[i].unBindCurrentFrameBuffer();
	}
}
void RenderSystem::renderBillBoards(vector<BillBoard> billboards)
{
	billboard_shader.bind();

	mat4x4 view = functions::createViewMatrix(State::camera);
	mat4x4 projection = functions::createProjectionMatrix(70, .1, 1000.f);
	billboard_shader.setUniform("view", view);
	billboard_shader.setUniform("sampler", 0);
	billboard_shader.setUniform("distMap", 6);
	billboard_shader.setUniform("projection", projection);

	for (int i = 0; i < billboards.size(); i++) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, billboards[i].texture->texture_id);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, billboards[i].texture->bloomMap);

		mat4x4 transformation = functions::createTransformationMatrix(billboards[i].position, vec3(0, 0, billboards[i].rotation), vec3(billboards[i].scale.x, billboards[i].scale.y, 1));
		transformation[0][0] = view[0][0] * billboards[i].scale.x;
		transformation[0][1] = view[1][0];
		transformation[0][2] = view[2][0];
		transformation[1][0] = view[0][1];
		transformation[1][1] = view[1][1] * billboards[i].scale.y;
		transformation[1][2] = view[2][1];
		transformation[2][0] = view[0][2];
		transformation[2][1] = view[1][2];
		transformation[2][2] = view[2][2];

		transformation = glm::rotate(transformation, billboards[i].rotation, vec3(0, 0, 1));

		transformation = view * transformation;
		billboard_shader.setUniform("transformation", transformation);

		billboard_shader.setUniform("rows", 1);
		billboard_shader.setUniform("columns", 1);

		glBindVertexArray(billboards[i].vao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, (GLsizei)billboards[i].draw_count, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


	billboard_shader.unBind();
}
void RenderSystem::renderShadow(vector<AnimatedMesh> models, vector<Light> lights)
{
	for (int i = 0; i < lights.size(); i++) {
		fbos[i].bindFrameBuffer();
		glClearColor(.3f, .3f, .3f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		anim_shadow_shader.bind();
		mat4x4 lightSpaces[4];
		mat4x4 projection = glm::ortho(-500.f, 500.f, -500.f, 500.f, -250.f, 2000.f);
		mat4x4 view = glm::lookAt(lights[i].position, vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
		mat4x4 lightSpace = projection * view;
		glm::translate(lightSpace, State::camera.pointToLookAt);
		lightSpaces[0] = lightSpace;

		anim_shadow_shader.setUniform("lightSpaceMatrix", lightSpace);

		for (int i = 0; i < models.size(); i++) {
			//if (!models[i].has_shadow) break;
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, models[i].texture->texture_id);

			glBindVertexArray(models[i].VertexArrayID);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);


			anim_shadow_shader.setUniform("shadowMap", 0);
			mat4x4 mat[50];
			for (int j = 0; j < models[i].bones.size(); j++) {

				mat4x4 rotMat = models[i].bones[j].rotation.toRotationMatrix();
				mat4x4 poseMat = functions::createTransformationMatrix(models[i].bones[j].position, vec3(0), vec3(1)) * rotMat;
				mat4x4 bindMat = models[i].bones[j].bindMatrix;
				bindMat = glm::inverse(bindMat);
				mat[j] = poseMat * bindMat;


			}

			anim_shadow_shader.setUniform("jointTransforms", mat, 50);
			anim_shadow_shader.setUniform("model", functions::createTransformationMatrix(models[i].position, models[i].rotation, models[i].transformation));


			glDrawElements(GL_TRIANGLES, (GLsizei)models[i].draw_count, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(4);

		}
		anim_shadow_shader.unBind();
		fbos[i].unBindCurrentFrameBuffer();
	}
}
RenderSystem::~RenderSystem()
{
}
