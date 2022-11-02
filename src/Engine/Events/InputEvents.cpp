#include "InputEvents.h"
#include "../Engine/Core/Hyko.h"
#include <iostream>

Window m_windowC;

void Hyko::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Hyko::m_keyCode = key;
	Hyko::m_keyAction = action;
}

void Hyko::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	m_mouseButton = button;
	m_mouseButtonAction = action;
}

bool Hyko::isKeyPressed(const Hyko::keyCode keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getMainGLFWWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return state == GLFW_PRESS;
}

bool Hyko::isMouseButtonPressed(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getMainGLFWWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return state == GLFW_PRESS;
}

bool Hyko::isKeyReleased(int keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getMainGLFWWindow());
	auto state = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return state == GLFW_RELEASE;
}

bool Hyko::isMouseButtonReleased(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getMainGLFWWindow());
	auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return state == GLFW_RELEASE;
}