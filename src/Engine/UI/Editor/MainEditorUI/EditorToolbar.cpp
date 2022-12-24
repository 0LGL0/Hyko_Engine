#include "EditorToolbar.h"
#include "../window.h"
#include "../Engine/Meshes/Entity.h"
#include "../Engine/Scene/Scene.h"

Hyko::Entity entity;
extern Hyko::Scene scene;

void Hyko::EToolbar::sceneData_Menu()
{
	std::string triangleCount = "Triangles in scene: " + std::to_string(scene.getComponentCount(HK_TRIANGLE));

	ImGui::Text(triangleCount.c_str());

}

void Hyko::EToolbar::create_Menu()
{
	if (ImGui::MenuItem("Triangle", nullptr, nullptr, &createIsOpen)) {
		entity.addToSceneTriangle();
		meshIsCreting = true;
	}
}

void Hyko::EToolbar::Christmas()
{
	ImGui::Text("Merry christmas!");
	ImGui::Text("Congratulations on the new year 2023");
}

void Hyko::EToolbar::createEToolbar()
{
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar
		| ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Toolbar", nullptr, winFlags);

	ImGui::SetWindowPos({ 0.0f, 0.0f });
	ImGui::SetWindowSize({ Hyko::getWinSize(Window::getMainGLFWWindow()).x, 1});

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Create")) {
			create_Menu();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene data")) {
			sceneData_Menu();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Christmas")) {
			Christmas();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
}
