#include "InputEvents.h"

Window m_windowC;


void Hyko::Input::resetInput()
{
	m_xOffset = 0.0;
	m_yOffset = 0.0;
	m_keyAction = -1;
	m_buttonAction = -1;
}

bool Hyko::Input::isKeyPressed(const Hyko::keyCode keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	m_keyAction = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return m_keyAction == GLFW_PRESS;
}

bool Hyko::Input::isMouseButtonPressed(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	m_buttonAction = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return m_buttonAction == GLFW_PRESS;
}

bool Hyko::Input::isKeyReleased(int keyCode)
{
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	m_keyAction = glfwGetKey(window, static_cast<int32_t>(keyCode));

	return m_keyAction == GLFW_RELEASE;
}

bool Hyko::Input::isMouseButtonReleased(int mouseButton) {
	auto* window = static_cast<GLFWwindow*>(m_windowC.getNativeWindow());
	m_buttonAction = glfwGetMouseButton(window, static_cast<int32_t>(mouseButton));

	return m_buttonAction == GLFW_RELEASE;
}

glm::vec2 Hyko::Input::getMousePos()
{
	return { m_mousePosX, m_mousePosY };
}

float Hyko::Input::getMouseXOffset()
{
	return m_xOffset;
}

float Hyko::Input::getMouseYOffset()
{
	return m_yOffset;
}

void Hyko::Input::setMouseXOffset(float value)
{
	m_xOffset = value;
}

void Hyko::Input::setMouseYOffset(float value)
{
	m_yOffset = value;
}

void Hyko::Input::setMouseXPos(float value)
{
	m_mousePosX = value;
}

void Hyko::Input::setMouseYPos(float value)
{
	m_mousePosY = value;
}
