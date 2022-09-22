#include "ImGuiWindows.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

void ImGuiWin::createImGuiWindow(GLFWwindow* glfwWindow)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiWin::createImGuiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiWin::ImGuiWindowDraw()
{
	ImGui::Begin("Test");

	ImGui::SliderFloat("PosX", &triangleNewPos.x, -1.0f, 1.0f);
	ImGui::SliderFloat("PosY", &triangleNewPos.y, -1.0f, 1.0f);

	ImGui::SliderFloat("ScaleX", &triangleNewScale.x, 0.0f, 5.0f);
	ImGui::SliderFloat("ScaleY", &triangleNewScale.y, 0.0f, 5.0f);

	ImGui::Text("Click on some Rot to make a triangle appear (the Rot function is experimental)");

	ImGui::Checkbox("RotX", &RotX);
	ImGui::Checkbox("RotY", &RotY);
	ImGui::Checkbox("RotZ", &RotZ);

	if (RotX) {
		axis += glm::vec3(1, 0, 0);
		if (!RotX) {
			axis -= glm::vec3(1, 0, 0);
		}
	}

	if (RotY) {
		axis += glm::vec3(0, 1, 0);
		if (!RotY) {
			axis -= glm::vec3(0, 1, 0);
		}
	}

	if (RotZ) {
		axis += glm::vec3(0, 0, 1);
		if (!RotZ) {
			axis -= glm::vec3(0, 0, 1);
		}
	}

	ImGui::SliderFloat("Rotate(experimental)", &triangleNewRotate, 0.0f, 360.0f);

	std::cout << "ImGuiPosSliderCount" << triangleNewPos.x << ' ' << triangleNewPos.y << std::endl;
	std::cout << "ImGuiScaleSliderCount" << triangleNewScale.x << ' ' << triangleNewScale.y << std::endl;
	std::cout << "ImGuiRotSliderCount" << triangleNewRotate << std::endl;

	ImGui::End();
}

void ImGuiWin::ImGuiRender()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWin::ImGuiWindowShutDown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
