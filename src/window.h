#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>

class Window {
public:
	GLFWwindow* window;

	int Cwidth = 0;
	int Cheight = 0;

	glm::vec2 windowSize;

	int WindowDraw(int width, int height);
	void WindowUpdate();
	void WindowShutDown();
};