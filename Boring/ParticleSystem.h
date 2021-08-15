#pragma once
#include "Texture.h"
#include <vector>
#include <glm/common.hpp>
#include "DataTypes.h"
#include <chrono>
#include "OBJLoader.h"
#include "EntityHandler.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace std;


struct Particle {

	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 velocity;
	int step;
	float life;
	Texture *texture;
};


class ParticleSystem : public Component<ParticleSystem>
{


public:
	ParticleSystem();
	ParticleSystem(Texture *tex);
	void emitParticle(glm::vec3 point);
	void update(glm::vec3 c, float dt);
	vector<Particle *> models;
	vector<Particle *> deleted;
	glm::vec3 emitVelocity;
	glm::vec3 randomVelocity;
	glm::vec3 force;
	glm::vec3 center;
	bool canEmmit;
	int max_particles;
	float ellapsed;
	float res;
	float pps;
	bool billboard;
	float life;
	bool from_center;
	bool has_trail;
	glm::vec4 custom_color;
	vector<ParticleSystem *> trail;
	ModelData *s;
	ModelData *shape;
	void clear();
	Texture * tex;
	int rows;
	int columns;
	float startSize;
	float finalSize;
	~ParticleSystem();
};
