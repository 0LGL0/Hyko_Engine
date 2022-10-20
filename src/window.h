#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>

class Window {
	GLFWwindow* window;

	int FPS;

	double ms;

	int Cwidth = 0;
	int Cheight = 0;

	unsigned int projUniformLocation;
	unsigned int transUniformLocation;
	unsigned int viewUniformLocation;
	unsigned int colorUniformLocation;

	glm::vec2 windowSize;

public:
	glm::mat4 projection;
	glm::mat4 view;

	int WindowDraw(int width, int height);
	void WindowUpdate();
	void WindowShutDown();
};

void windowResizeCallback(GLFWwindow* window, int width, int height);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);