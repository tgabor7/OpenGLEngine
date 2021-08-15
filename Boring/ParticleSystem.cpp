#include "ParticleSystem.h"
#include <glm\geometric.hpp>
#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

ParticleSystem::ParticleSystem()
{
}
ParticleSystem::ParticleSystem(Texture *tex)
{
	trail = vector<ParticleSystem *>();
	ellapsed = 0;
	from_center = 1;
	models = vector<Particle *>();
	has_trail = false;
	max_particles = 100;
	pps = 10.f;
	canEmmit = false;
	billboard = false;
	res = 0.25;
	this->tex = tex;
	life = 5;
	force = glm::vec3(0, 1, 0);
	custom_color = glm::vec4(1, .3, 0, 1);
	emitVelocity = glm::vec3(0, 1, 0);
	randomVelocity = glm::vec3(10, 0, 10);
	srand(time(NULL));
	s = OBJLoader::loadOBJp("objs/cube.obj");
	shape = OBJLoader::loadOBJp("objs/cube.obj");
	rows = 4;
	columns = 5;
	startSize = 10;
	finalSize = 0;

}
void ParticleSystem::emitParticle(glm::vec3 point)
{
	center = point;
	if (models.size() >= max_particles) return;
	if (canEmmit) {

		for (int i = -1 + 1 / res; i < s->vertices.size() * res / 3; i += 1 / res) {
			glm::vec3 v(s->vertices[i * 3], s->vertices[i * 3 + 1], s->vertices[i * 3 + 2]);
			v += center;
			if (from_center) {
				v = glm::vec3(center);
				emitVelocity = -glm::vec3(s->vertices[i * 3], s->vertices[i * 3 + 1], s->vertices[i * 3 + 2]);
			}
			Particle *p = new Particle;
			*p = { v,
				glm::vec3(startSize),
				glm::vec3(0),
				emitVelocity,
				0,
				life,
				tex };
			models.push_back(p);
			if (has_trail) {
				ParticleSystem *t = new ParticleSystem(tex);
				t->pps = 100;
				t->max_particles = 1000;
				t->life = life;
				t->emitVelocity = glm::vec3();
				t->randomVelocity = glm::vec3();
				t->s->vertices = { models[i]->position.x,models[i]->position.y,models[i]->position.z };
				t->billboard = true;
				t->res = 1;
				trail.push_back(t);
			}

		}

	}
}

void ParticleSystem::update(glm::vec3 c, float dt)
{

	for (int i = 0; i < trail.size(); i++) {
		trail[i]->emitParticle(center);
		trail[i]->s->vertices = { models[i]->position.x,models[i]->position.y,models[i]->position.z };
		trail[i]->update(c, dt);
	}
	canEmmit = false;
	ellapsed += dt;
	if (ellapsed >= 1.0 / pps) {
		ellapsed = 0;
		canEmmit = true;
	}

	for (int i = 0; i < models.size(); i++) {
		models[i]->scale = glm::vec3((models[i]->life / life)*(finalSize - startSize));
		models[i]->life -= dt;
		models[i]->position += models[i]->velocity * dt;
		models[i]->velocity += force * .001f;
		if (randomVelocity.x != 0) models[i]->velocity.x += (rand() % 1000 - 500) * 0.00001f * randomVelocity.x;
		if (randomVelocity.y != 0) models[i]->velocity.y += (rand() % 1000 - 500) * 0.00001f * randomVelocity.y;
		if (randomVelocity.z != 0) models[i]->velocity.z += (rand() % 1000 - 500) * 0.00001f * randomVelocity.z;


		if (models[i]->life < 0) {
			delete models[i];
			models.erase(models.begin() + i);
			if (has_trail) {
				delete trail[i];
				trail.erase(trail.begin() + i);
			}

		}
	}

}

void ParticleSystem::clear() {
	for (int i = 0; i < models.size(); i++) {
		delete models[i];
	}
	models.clear();
}
ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < models.size(); i++) {
		delete models[i];
	}
}
