#include "TransformationSystem.h"



TransformationSystem::TransformationSystem()
{
	addComponentType(Transformation::type);
	addComponentType(Mesh::type);
}
void TransformationSystem::updateSystem(double delta)
{

}
void TransformationSystem::updateComponents(double delta)
{
	Transformation* t = (Transformation*)getComponent(Transformation::type)[0];
	Mesh *m = (Mesh*)getComponent(Mesh::type)[0];
	m->position = t->pos;
	m->rotation = t->rotation;
	m->scale = t->scale;
}


TransformationSystem::~TransformationSystem()
{
}
