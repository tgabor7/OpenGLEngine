#pragma once
#define GLEW_STATIC
#include "FrameBuffer.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Window.h"
#include <ctime>
#include <chrono>
#include "EntityHandler.h"
#include "DataTypes.h"
#include "Input.h"
#include "actions.h"

#define SMALL 0
#define MEDIUM 1
#define LARGE 2

using namespace std;

class State
{
public:
	bool running;
	GLFWwindow * window;
	Window win;
	State();
	void run();
	EntityHandler handler;
	double delta = 0;
	double frame_cap;
	virtual void update() = 0;
	virtual void init() = 0;
	virtual void render() = 0;
	static bool fullscreen;
	static bool vsync;
	static int WIDTH;
	static int HEIGHT;
	static int BLOOM_SIZE;
	static Camera camera;
	static Input *input;
	static FrameBuffer *fbo;
	static bool draw_boundingboxes;
	vec2 Mouse;
	~State();
private:
	void updateCamera(Camera &c);
	double time = static_cast<double>(std::clock());
	double get_time();
	double unprocessed = 0;
	double frame_time = 0;
	int frames = 0;
	double passed = 0;
	double lastFrameTime = 0;
};

