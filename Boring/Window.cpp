#include "Window.h"

Window::Window()
{
}
void Window::createWindow(const char* title, int width, int height, bool fullscreen,bool vsync) {

	this->fullscreen = fullscreen;
	Window::title = (char *)title;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

	if (window == NULL)
		throw std::invalid_argument("Couldn't create window!");


	if (!fullscreen) {

		GLFWvidmode vid = *glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(window, (vid.width - width) / 2, (vid.height - height) / 2);
		glfwShowWindow(window);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);

}

int Window::shouldClose() {
	return glfwWindowShouldClose(window);
}
void Window::swapBuffers(bool f) {

	glfwSwapBuffers(window);
	
}
void Window::resize(int width, int height, bool fullscreen) {


	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	if (fullscreen) {
		glfwSetWindowMonitor(window, monitor, 0, 0, width, height, 0);
	}
	else {

		glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, 0);
		glfwSetWindowPos(window, (mode->width - width) / 2, (mode->height - height) / 2);
	}

}
Window::~Window()
{
}
