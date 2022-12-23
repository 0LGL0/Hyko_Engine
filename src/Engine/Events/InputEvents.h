#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include "../window.h"
#include "../Engine/Core/Hyko.h"

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