#include "ImGuiWindows.h"
//#include "../Engine/Debug/Debug.h"
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

void ImGuiWin::ImGui_MainWindowDraw()
{
	ImGui::Begin("Main window");

	ImGui::Checkbox("Debug", &DebugWindowShow);
	ImGui::Checkbox("Display settings", &DisplaySettingsShow);
	ImGui::Checkbox("Scene settings", &SceneSettingsShow);

	ImGui::End();
}

void ImGuiWin::ImGui_DebugWindowDraw(int fps, double dt)
{
	static const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	FPSTitle = "Editor window FPS: " + std::to_string(fps);
	dtTitle = "Editor window DeltaTime: " + std::to_string(dt) + "ms";

	ImGui::Begin("Debug");

	if (ImGui::TreeNodeEx("Counters", treeFlags)) {
		ImGui::Text(FPSTitle.c_str());
		ImGui::Text(dtTitle.c_str());

		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Scene edit", treeFlags)) {
		ImGui::Checkbox("Render only edges for meshes", &meshRenderLineOnly);
		ImGui::TreePop();
	}

	ImGui::End();
}

void ImGuiWin::ImGui_DisplaySettingsWindowDraw()
{
	ImGui::Begin("Display settings");

	ImGui::Checkbox("VSync", &vsync);

	ImGui::End();
}

void ImGuiWin::ImGui_SceneSettingsWindowDraw()
{
	ImGui::Begin("Scene settings");

	ImGui::ColorEdit4("Sky box color", m_skyBoxColor);

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
