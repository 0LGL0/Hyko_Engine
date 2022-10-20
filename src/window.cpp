#include <glad/glad.h>
#include "window.h"
#include "shader.h"
#include "Engine/Debug/Debug.h"
#include "Engine/Meshes/Triangle.h"
#include "Engine/ImGui/ImGuiWindows.h"
#include "Engine/Projection/EditorProjection.h"
//#include "Engine/Events/EditorInput.h"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

ImGuiWin GuiWindow;

int Window::WindowDraw(int width, int height)
{
	Debug debug;
	EProjection EProj;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	Cwidth = width;
	Cheight = height;

	window = glfwCreateWindow(Cwidth, Cheight, "Hyko", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);

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

	projection = EProj.createOrthoProjection(-1.0f, 1.0f, -1.0f, 1.0f);
	view = EProj.createViewMatrix(glm::vec3(0.0f, 0.0f, 0.0f));

	debug.edgeRenderingOnly(false);

	return 0;
}

void Window::WindowUpdate()
{
	Triangle triangle;
	Debug debug;
	Shader shader;

	unsigned int shaderProgram = triangle.createShader("res//vertexShader.glsl", "res//fragmentShader.glsl");
	glBindVertexArray(triangle.createVAO());

	while (!glfwWindowShouldClose(window)) {
		FPS = debug.getFPS();
		ms = debug.getDeltaTime();

		if (GuiWindow.vsync) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		glClearColor(GuiWindow.skySphereColor[0], GuiWindow.skySphereColor[1], GuiWindow.skySphereColor[2], GuiWindow.skySphereColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		GuiWindow.createImGuiNewFrame();

		if (GuiWindow.createTriangle) {
			glUseProgram(shaderProgram);

			triangle.setScale(shaderProgram, GuiWindow.triangleNewScale);
			triangle.translate(shaderProgram, GuiWindow.triangleNewPos);

			transUniformLocation = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transUniformLocation, 1, GL_FALSE, glm::value_ptr(triangle.createTransformMatrix()));
		}

		viewUniformLocation = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

		projUniformLocation = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

		colorUniformLocation = glGetUniformLocation(shaderProgram, "inColor");
		glUniformMatrix4fv(colorUniformLocation, 1, GL_FALSE, glm::value_ptr(triangle.getColorFromGUI()));

		if(GuiWindow.createTriangle) glDrawArrays(GL_TRIANGLES, 0, 3);

		////ImGui. Hyko GUI windows////////////////////////////////////////////////////////////////

		GuiWindow.ImGui_MainWindowDraw();
		GuiWindow.ImGui_SceneComponentsWindowDraw();
		GuiWindow.ImGui_HykoPrimitiveMeshes();

		if (GuiWindow.DebugWindowShow)																						   GuiWindow.ImGui_DebugWindowDraw(FPS, ms);
		if (GuiWindow.DisplaySettingsShow)																					   GuiWindow.ImGui_DisplaySettingsWindowDraw();
		if (GuiWindow.createTriangle /*|| GuiWindow.createRectangle || GuiWindow.createCircle || GuiWindow.createStaticMesh*/) GuiWindow.ImGui_HykoPrimitiveMeshesEdit();
		if (GuiWindow.SceneSettingsShow)																					   GuiWindow.ImGui_SceneSettingsWindowDraw();

		///////////////////////////////////////////////////////////////////////////////////////////

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

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	EProjection EProj;
	Window windowC;

	glViewport(0, 0, width, height);

	windowC.projection = EProj.resizeOrthoProjection(width, height);
}

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//	EInput eIn;
//	EProjection EProj;
//	Window windowC;
//
//	//if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
//		if (key == GLFW_KEY_W && action == GLFW_PRESS) {
//			windowC.view = EProj.createViewMatrix(eIn.EditorCameraControl('w'));
//		}
//	//}
//		
//}