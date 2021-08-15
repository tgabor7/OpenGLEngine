#include "AnimatedMeshRenderer.h"



AnimatedMeshRenderer::AnimatedMeshRenderer()
{
	shader = AnimatedShader("shaders/animation");
	projection = functions::createProjectionMatrix(70, .1, 1000);
}
void AnimatedMeshRenderer::render(vector<AnimatedMesh> models,vector<Light> lights, vector<ShadowFrameBuffer> fbos) {
	mat4x4 view = functions::createViewMatrix(State::camera);
	mat4x4 lightSpaces[4];

	for (int i = 0; i < lights.size(); i++) {
		mat4x4 projection = glm::ortho(-500.f, 500.f, -500.f, 500.f, -250.f, 2000.f);
		mat4x4 view = glm::lookAt(lights[i].position, vec3(0.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f));
		mat4x4 lightSpace = projection * view;
		glm::translate(lightSpace, State::camera.pointToLookAt);
		lightSpaces[i] = lightSpace;

	}

	vec3 lightsp[4];
	for (int i = 0; i < lights.size(); i++) {
		lightsp[i] = lights[i].position;
	}

	vec3 lightsc[4];
	for (int i = 0; i < lights.size(); i++) {
		lightsc[i] = lights[i].color;
	}

	vec3 attenuation[4];
	for (int i = 0; i < lights.size(); i++) {
		attenuation[i] = lights[i].attenuation;
	}
	shader.bind();
	shader.setUniform("sampler", 0);
	shader.setUniform("distMap", 6);
	shader.setUniform("lightSpaceMatrix", lightSpaces);
	shader.setUniform("projection", projection);
	shader.setUniform("view", view);

	shader.setUniform("lightPosition", lightsp);
	shader.setUniform("lightColor", lightsc);
	shader.setUniform("attenuation", attenuation);
	shader.setUniform("numberOfLights", (int)lights.size());
	for (int j = 0; j < models.size(); j++) {
		shader.setUniform("transformation", functions::createTransformationMatrix(models[j].position, models[j].rotation, models[j].transformation));
		for (int i = 0; i < models[j].bones.size(); i++) {

			mat4x4 rotMat = models[j].bones[i].rotation.toRotationMatrix();
			mat4x4 poseMat = functions::createTransformationMatrix(models[j].bones[i].position, vec3(0), vec3(1)) * rotMat;
			mat4x4 bindMat = models[j].bones[i].bindMatrix;
			bindMat = glm::inverse(bindMat);
			mat[i] = poseMat * bindMat;


		}

		shader.setUniform("jointTransforms", mat, 50);
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, models[j].texture->texture_id);
		if (fbos.size() > 0) {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, fbos[0].depthMap);

		}
		for (int i = 1; i < fbos.size(); i++) {

			glActiveTexture(GL_TEXTURE3 + i - 1);
			glBindTexture(GL_TEXTURE_2D, fbos[i].depthMap);

		}
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, models[j].texture->speculatTexture);

		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, models[j].texture->bloomMap);

		glBindVertexArray(models[j].VertexArrayID);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);
		glDrawElements(GL_TRIANGLES, models[j].draw_count, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	shader.unBind();
}

AnimatedMeshRenderer::~AnimatedMeshRenderer()
{
}
