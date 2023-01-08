#pragma once

// input
#include "Engine/Core/KeyKodes.h"
#include "Engine/Core/MouseButtons.h"

#include "GL/Window/window.h"

// GL
#include <glfw3.h>

// GL / Maths
#include <glm/glm.hpp>

namespace Hyko {
	static float m_mousePosX = 0.0f;
	static float m_mousePosY = 0.0f;

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	bool isKeyPressed(const Hyko::keyCode keyCode);
	bool isMouseButtonPressed(int mouseButton);

	bool isKeyReleased(int keyCode);
	bool isMouseButtonReleased(int mouseButton);

	// getters
	glm::vec2 getMousePos();
}