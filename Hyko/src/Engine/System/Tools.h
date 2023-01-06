#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>

namespace Hyko {
	static int m_windowSizeX;
	static int m_windowSizeY;

	glm::vec2 getWinSize(GLFWwindow* window);
}