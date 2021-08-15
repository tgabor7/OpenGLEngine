#pragma once
#include "State.h"

class PhysicsTest : public State
{
public:
	PhysicsTest();
	void init();
	void render();
	void update();

	~PhysicsTest();
};

