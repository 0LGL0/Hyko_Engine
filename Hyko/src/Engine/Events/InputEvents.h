#pragma once

#include "GL/Window/window.h"
#include "../Engine/Core/Hyko.h"

#include <glfw3.h>
#include <glm/glm.hpp>

namespace Hyko {
	static float m_mousePosX = 0.0f;
	static float m_mousePosY = 0.0f;

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	bool isKeyPressed(const Hyko::keyCode keyCode);
	bool isMouseButtonPressed(int mouseButton);

	bool isKeyReleased(int keyCode);
	bool isMouseButtonReleased(int mouseButton);

	glm::vec2 getMousePos();
}