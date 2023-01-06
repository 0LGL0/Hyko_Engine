#include "InputEvents.h"
#include <iostream>

Window m_windowC;

void Hyko::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	m_mousePosX = xpos;
	m_mousePosY = ypos;
}

bool Hyko::isKeyPressed(const Hyko::keyCode keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return state == GLFW_PRESS;
}

bool Hyko::isMouseButtonPressed(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return state == GLFW_PRESS;
}

bool Hyko::isKeyReleased(int keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return state == GLFW_RELEASE;
}

bool Hyko::isMouseButtonReleased(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return state == GLFW_RELEASE;
}

glm::vec2 Hyko::getMousePos()
{
	return { m_mousePosX, m_mousePosY };
}
