#pragma once
#include <glfw3.h>

class Window {
public:
	GLFWwindow* window;

	int WindowDraw(int weight, int height);
	void WindowUpdate();
	void WindowShutDown();
};