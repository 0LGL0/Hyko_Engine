#pragma once

#include "Engine/Events/UpdateEvents.h"
#include "Engine/Core/Hyko.h"
#include <glfw3.h>
#include <glm/glm.hpp>

class Window {
private:
	static GLFWwindow* m_window;

	
private:
	int FPS = 0;

	unsigned int projUniformLocation = 0;
	unsigned int viewUniformLocation = 0;

	float m_LastFrameTime = 0.0f;
public:
	glm::mat4 projection;
	glm::mat4 view;

	static GLFWwindow* getMainGLFWWindow() { return m_window; };

	int WindowDraw(int width, int height);
	void WindowUpdate();
	void WindowShutDown();
};

void windowResizeCallback(GLFWwindow* window, int width, int height);