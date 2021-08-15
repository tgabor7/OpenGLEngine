#include "ParticleRenderer.h"

#include "MovementSystem.h"
#include "Mesh.h"

MovementSystem::MovementSystem()
{
	addComponentType(ParticleSystem::type);
}
void MovementSystem::updateSystem(double delta)
{
	
}
void MovementSystem::updateComponents(double delta)
{
	ParticleSystem* ps = (ParticleSystem*)getComponent(ParticleSystem::type)[0];
	ps->pps = 20;
	ps->max_particles = 9999;
	ps->res = .8;
	ps->randomVelocity = vec3(20);
	ps->force = vec3(0, 80, 0);
	ps->billboard = 1;
	ps->life = 2;
	ps->from_center = 1;
	ps->startSize = 1;
	ps->update(State::camera.position, delta);
}
MovementSystem::~MovementSystem()
{
}
