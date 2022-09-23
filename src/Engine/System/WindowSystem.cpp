#include "WindowSystem.h"
#include <iostream>

bool WindowSys::WindowIsResizable(GLFWwindow* window, const int width, const int height)
{
	int newWidth;
	int newHeight;

	glfwGetWindowSize(window, &newWidth, &newHeight);
	if (width > newWidth || width < newWidth || height > newHeight || height < newHeight) {
		std::cout << "Window resized" << std::endl;
		return true;
	}
	else {
		return false;
	}
}

glm::vec2 WindowSys::resizeGlViewport(GLFWwindow* glfwWindow, int width, int height)
{
	int winWidth;
	int winHeight;

	glm::vec2 windowSize;

	glfwGetWindowSize(glfwWindow, &winWidth, &winHeight);
	glViewport(0, 0, winWidth, winHeight);

	windowSize.x = winWidth;
	windowSize.y = winHeight;

	return windowSize;
}
