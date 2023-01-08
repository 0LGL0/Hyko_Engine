#pragma once

// GL
#include <glfw3.h>

// GL / Maths
#include <glm/glm.hpp>

namespace Hyko {
	static int m_windowSizeX;
	static int m_windowSizeY;

	glm::vec2 getWinSize(GLFWwindow* window);
}