#pragma once
#include "Transformation.h"
#include "System.h"
#include "AnimatedMesh.h"

class AnimatedTransformationSystem : public System
{
public:
	AnimatedTransformationSystem();
	void updateSystem(double delta);
	void updateComponents(double delta);
	~AnimatedTransformationSystem();
};

