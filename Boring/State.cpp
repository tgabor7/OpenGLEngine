#include "GL/glew.h"
#include "State.h"
#include "RenderSystem.h"
#include "PostRenderSystem.h"
#include "MovementSystem.h"
#include "TransformationSystem.h"
#include "AnimatedTransformationSystem.h"
#include "GuiRenderSystem.h"
#include "SAT.h"
#include "BoundingBoxRenderer.h"

int State::WIDTH = 800;
int State::HEIGHT = 600;
bool State::fullscreen = false;
bool State::vsync = false;
bool State::draw_boundingboxes = false;
int State::BLOOM_SIZE = MEDIUM;
Camera State::camera;
Input *State::input = nullptr;
FrameBuffer* State::fbo = nullptr;

State::State()
{
	frame_cap = 1.0 / 60.0;
	vsync = 0;
}
double State::get_time() {
	return (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / (double)1000000000L;

}
void State::run()
{
	if (vsync) frame_cap = 1.0 / 60.0;
	time = get_time();
	glfwInit();

	
	win.createWindow("title", WIDTH, HEIGHT, fullscreen,vsync);


	running = true;
	glewInit();
	input = new Input(win.window, WIDTH, HEIGHT);
	fbo = new FrameBuffer(WIDTH, HEIGHT);
	init();
	camera.distance = 100;
	RenderSystem render_system;
	PostRenderSystem post_system;
	MovementSystem movement_system;
	TransformationSystem t_system;
	AnimatedTransformationSystem at_system;
	GuiRenderSystem gui_render_system;
	SAT sat;
	BoundingBoxRenderer bounding_renderer;
	ClothSystem cloth_system;
	while (win.shouldClose() != 1 && running) {
		bool can_render = false;


		double time_2 = get_time();
		passed = time_2 - time;
		unprocessed += passed;
		frame_time += passed;

		time = time_2;

		while (unprocessed >= frame_cap) {
			delta = (get_time() - lastFrameTime);
			if (delta > 100) delta = 0;
			lastFrameTime = get_time();
			unprocessed -= frame_cap;
			can_render = true;
			
			updateCamera(camera);
			update();
			movement_system.update(delta);
			t_system.update(delta);
			at_system.update(delta);
			sat.update(delta);
			if (frame_time >= 1.0) {

				frame_time = 0;


				cout << frames << endl;
				frames = 0;
			}
		}
		if (can_render) {
			glClearColor(.3f, .3f, .3f, 1);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_MULTISAMPLE);
			
			render_system.update(delta);
			post_system.update(delta);
			gui_render_system.update(delta);
			if(draw_boundingboxes) bounding_renderer.update(delta);

			win.swapBuffers(0);
			glfwPollEvents();

			frames++;
		}

	}
	glfwDestroyWindow(win.window);
	glfwTerminate();
}
void State::updateCamera(Camera &c)
{
	if (camera.angley > 89.0F) {
		camera.angley = 89.0F;
	}
	if (camera.angley < -89.0F) {
		camera.angley = -89.0F;
	}


	camera.position.x = (camera.distance * -(float)sin(camera.anglex*3.14159265 / 180)
		* (float)cos(camera.angley*3.14159265 / 180) + camera.pointToLookAt.x);
	camera.position.y = (camera.distance * -(float)sin(camera.angley*3.14159265 / 180)
		+ camera.pointToLookAt.y);
	camera.position.z = (-camera.distance * (float)cos(camera.anglex*3.14159265 / 180)
		* (float)cos(camera.angley*3.14159265 / 180) + camera.pointToLookAt.z);
	Mouse = input->getMouse();
}
State::~State()
{
}
