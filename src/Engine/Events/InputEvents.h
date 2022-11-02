#pragma once
#include <glfw3.h>
#include "../window.h"

namespace Hyko {
	static int m_keyCode;
	static int m_keyAction;
	static int m_mouseButton;
	static int m_mouseButtonAction;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	bool isKeyPressed(const Hyko::keyCode keyCode);
	bool isKeyPressedLoop(int keyCode);
	bool isMouseButtonPressed(int mouseButton);
	bool isMouseButtonPressedLoop(int mouseButton);

	bool isKeyReleased(int keyCode);
	bool isMouseButtonReleased(int mouseButton);
}