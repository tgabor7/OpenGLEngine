#include "TestState.h"

int main() {
	TestState *state = new TestState();
	state->WIDTH = 800;
	state->HEIGHT = 600;
	state->fullscreen = false;
	state->BLOOM_SIZE = SMALL;
	state->frame_cap = 1.0 / 60.0;
	state->vsync = true;
	state->draw_boundingboxes = true;
	state->run();
	delete state;
	return 0;
}