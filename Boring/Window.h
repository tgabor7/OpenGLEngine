#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window
{
public:
	Window();
	GLFWwindow* window;
	void createWindow(const char* title, int width, int height, bool fullscreen,bool vsync);
	char* title;
	bool fullscreen;
	~Window();
	void swapBuffers(bool f);
	void resize(int width, int height, bool fullscreen);
	int shouldClose();
};
