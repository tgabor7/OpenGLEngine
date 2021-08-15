#include "AnimatedTransformationSystem.h"



AnimatedTransformationSystem::AnimatedTransformationSystem()
{
	addComponentType(Transformation::type);
	addComponentType(AnimatedMesh::type);
}
void AnimatedTransformationSystem::updateSystem(double delta)
{

}
void AnimatedTransformationSystem::updateComponents(double delta)
{
	Transformation* t = (Transformation*)getComponent(Transformation::type)[0];
	AnimatedMesh *m = (AnimatedMesh*)getComponent(AnimatedMesh::type)[0];
	m->position = t->pos;
	m->rotation = t->rotation;
	m->transformation = t->scale;
}


AnimatedTransformationSystem::~AnimatedTransformationSystem()
{
}
