#include <glad/glad.h>
#include "window.h"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

Hyko::EUpdates updates;
ImGuiWin GuiWindow;

GLFWwindow* Window::m_window;

int Window::WindowDraw(int width, int height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, "Hyko", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, windowResizeCallback);

	if (!m_window) {
		std::cout << "Window not initialized" << std::endl;
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GuiWindow.createImGuiWindow(m_window);

	updates.EventStart();

	return 0;
}

void Window::WindowUpdate()
{
	while (!glfwWindowShouldClose(m_window)) {
		////DeltaTime (Seconds | Milliseconds)/////////////////////////

		float time = (float)glfwGetTime();
		Hyko::Time ts = time - m_LastFrameTime;
		m_LastFrameTime = time;

		///////////////////////////////////////////////////////////////

		updates.EventUpdate(ts);

		GuiWindow.ImGuiRender();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Window::WindowShutDown()
{
	GuiWindow.ImGuiWindowShutDown();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}