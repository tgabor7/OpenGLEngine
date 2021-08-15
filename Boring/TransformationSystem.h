#pragma once
#include "Transformation.h"
#include "System.h"
#include "Mesh.h"

class TransformationSystem : public System
{
public:
	TransformationSystem();
	void updateSystem(double delta);
	void updateComponents(double delta);
	~TransformationSystem();
};

