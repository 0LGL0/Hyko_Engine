#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <../Engine/Meshes/Triangle.h>

class ImGuiWin {
public:
	glm::vec3 triangleNewPos;
	glm::vec3 triangleNewScale = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::vec3 axis;

	float triangleNewRotate;

	bool RotX;
	bool RotY;
	bool RotZ;

	void createImGuiWindow(GLFWwindow* glfwWindow);
	void createImGuiNewFrame();
	void ImGuiWindowDraw();
	void ImGuiRender();
	void ImGuiWindowShutDown();
};
