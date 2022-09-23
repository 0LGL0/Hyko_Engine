#pragma once
#include <glfw3.h>
#include "glm/glm.hpp"

class WindowSys {
public:
	bool WindowIsResizable(GLFWwindow* window, const int width, const int height);
	glm::vec2 resizeGlViewport(GLFWwindow* glfwWindow, int width, int height);
};
