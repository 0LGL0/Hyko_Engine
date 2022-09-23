#include <glad/glad.h>
#include "window.h"
#include "Engine/Debug.h"
#include "Engine/Meshes/Triangle.h"
#include "Engine/ImGui/ImGuiWindows.h"
#include "Engine/System/WindowSystem.h"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

Debug debug;
Triangle triangle;
ImGuiWin GuiWindow;
WindowSys WSys;

int Window::WindowDraw(int width, int height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	Cwidth = width;
	Cheight = height;

	window = glfwCreateWindow(Cwidth, Cheight, "test", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!window) {
		std::cout << "Window not initialized" << std::endl;
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GuiWindow.createImGuiWindow(window);

	debug.edgeRenderingOnly(false);

	return 0;
}

void Window::WindowUpdate()
{
	unsigned int shaderProgram = triangle.createShader("res//vertexShader.glsl", "res//fragmentShader.glsl");

	while (!glfwWindowShouldClose(window)) {
		if (WSys.WindowIsResizable(window, Cwidth, Cheight) == true) {
			windowSize = WSys.resizeGlViewport(window, Cwidth, Cheight);
			
			Cwidth = windowSize.x;
			Cheight = windowSize.y;
		}

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		GuiWindow.createImGuiNewFrame();

		glUseProgram(shaderProgram);

		triangle.setScale(shaderProgram, GuiWindow.triangleNewScale);
		triangle.setRotate(shaderProgram, GuiWindow.triangleNewRotate, GuiWindow.axis);
		triangle.translate(shaderProgram, GuiWindow.triangleNewPos);

		unsigned int transUniformLocation = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transUniformLocation, 1, GL_FALSE, glm::value_ptr(triangle.createTransformMatrix()));

		glBindVertexArray(triangle.createVAO());
		glDrawArrays(GL_TRIANGLES, 0, 3);

		GuiWindow.ImGuiWindowDraw();

		GuiWindow.ImGuiRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Window::WindowShutDown()
{
	GuiWindow.ImGuiWindowShutDown();
	glfwDestroyWindow(window);
	glfwTerminate();
}