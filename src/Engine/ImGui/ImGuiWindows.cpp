#include "ImGuiWindows.h"
#include "../Engine/Debug/Debug.h"
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

void ImGuiWin::ImGui_DebugWindowDraw(int fps, double ms)
{
	FPSTitle = "Editor window FPS: " + std::to_string(fps);
	msTitle = "Editor window ms: " + std::to_string(ms);

	ImGui::Begin("Debug");

	ImGui::Text(FPSTitle.c_str());
	ImGui::Text(msTitle.c_str());

	ImGui::End();
}

void ImGuiWin::ImGui_DisplaySettingsWindowDraw()
{
	ImGui::Begin("Dispaly settings");

	ImGui::Checkbox("VSync", &vsync);

	ImGui::End();
}

void ImGuiWin::ImGui_SceneComponentsWindowDraw()
{
	static const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	ImGui::Begin("Scene components");

	if (ComponentSettings_TreeShow) {
		if (ImGui::TreeNodeEx(componentTreeName.c_str(), treeFlags)) {
			ImGui::TreePop();
		}
	}

	ImGui::End();
}

void ImGuiWin::ImGui_SceneSettingsWindowDraw()
{
	ImGui::Begin("Scene settings");

	ImGui::ColorEdit4("Sky box color", skySphereColor);

	ImGui::End();
}

void ImGuiWin::ImGui_HykoPrimitiveMeshes()
{
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Primitive meshes");

	if (ImGui::Button("Triangle", ImVec2(70.0f, 25.0f))) {
		triangleCount++;
		componentTreeName = "Triangle." + std::to_string(triangleCount);
		ComponentSettings_TreeShow = true;
		createTriangle = true; 
	}

	ImGui::End();
}

void ImGuiWin::ImGui_HykoPrimitiveMeshesEdit()
{
	static ImGuiSliderFlags Sliderflags = ImGuiSliderFlags_None;

	ImGui::Begin("Mesh edit");

	if (createTriangle) {
		ImGui::DragFloat("Pos X", &triangleNewPos.x, 0.01f, -FLT_MAX, FLT_MAX, NULL, Sliderflags);
		ImGui::DragFloat("Pos Y", &triangleNewPos.y, 0.01f, -FLT_MAX, FLT_MAX, NULL, Sliderflags);

		ImGui::DragFloat("Scale X", &triangleNewScale.x, 0.01f, -FLT_MAX, FLT_MAX, NULL, Sliderflags);
		ImGui::DragFloat("Scale Y", &triangleNewScale.y, 0.01f, -FLT_MAX, FLT_MAX, NULL, Sliderflags);

		//ImGui::ColorEdit4("Triangle color", triangleColor);
	}

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
