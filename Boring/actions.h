#pragma once
#include "EntityHandler.h"
#include "ParticleSystem.h"
#include "Transformation.h"
#include "AnimatedMesh.h"
#include "SAT.h"

class action {
public:
	static void emit(int entity) {
		ParticleSystem *psys = (ParticleSystem*)EntityHandler::getComponent(entity, ParticleSystem::type);
		psys->emitParticle(vec3(0));
	}
	static void translate(int entity, vec3 v) {
		Transformation *t = (Transformation*)EntityHandler::getComponent(entity, Transformation::type);
		t->pos += v;
	}
	static void setRotation(int entity, vec3 r) {
		Transformation *t = (Transformation*)EntityHandler::getComponent(entity, Transformation::type);
		t->rotation = r;
	}
	static void rotate(int entity, float angle, vec3 axis) {
		Transformation *t = (Transformation*)EntityHandler::getComponent(entity, Transformation::type);
		t->rotation += angle * axis;
	}
	static vec3 getRotation(int entity) {
		Transformation *t = (Transformation*)EntityHandler::getComponent(entity, Transformation::type);
		return t->rotation;
	}
	static void stepAnimation3D(int entity) {
		AnimatedMesh *anim = (AnimatedMesh*)EntityHandler::getComponent(entity, AnimatedMesh::type);
	}
	static void setFrame(int entity,int f) {
		AnimatedMesh *anim = (AnimatedMesh*)EntityHandler::getComponent(entity, AnimatedMesh::type);
		if (anim == nullptr) return;
		anim->setFrame(f);
	}
};