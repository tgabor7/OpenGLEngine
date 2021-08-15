#pragma once
#include "system.h"
class MovementSystem : public System
{
public:
	MovementSystem();
	void updateSystem(double delta);
	void updateComponents(double delta);
	~MovementSystem();
};

