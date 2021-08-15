#pragma once
#include "State.h"

class TestState : public State
{
public:
	TestState();
	void init();
	void render();
	void update();

	~TestState();
};

