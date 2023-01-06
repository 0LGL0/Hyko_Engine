#include "EditorToolbar.h"

#include "GL/Window/window.h"
#include "Engine/Debug/Debug.h"

void Hyko::EToolbar::scene_Menu()
{
	const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	if (ImGui::TreeNodeEx("Data", treeFlags)) {
		std::string triangleCount = "Triangles in scene: " + std::to_string(m_scene->getComponentCount(HK_TRIANGLE));
		ImGui::Text(triangleCount.c_str());

		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Settings", treeFlags)) {
		ImGui::ColorEdit3("Scene background color", backgroundColor);

		ImGui::TreePop();
	}

}

void Hyko::EToolbar::create_Menu()
{
	if (ImGui::MenuItem("Triangle", nullptr, nullptr, &createIsOpen)) {
		m_entity->addToSceneTriangle();
		meshIsCreting = true;
	}
}

void Hyko::EToolbar::debug(int FPS, float dt)
{
	const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	std::string dt_s = "Delta time: " + std::to_string(dt);
	std::string fps_s = "FPS: " + std::to_string(FPS);

	ImGui::Begin("Debug");

	if (ImGui::TreeNodeEx("Counters", treeFlags)) {
		ImGui::Text(dt_s.c_str());
		ImGui::Text(fps_s.c_str());

		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Scene edit", treeFlags)) {
		ImGui::Checkbox("Show mesh edges", &meshLineMode);

		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Display settings", treeFlags)) {
		ImGui::Checkbox("VSync", &VSync);

		ImGui::TreePop();
	}

	ImGui::End();
}

void Hyko::EToolbar::Christmas()
{
	ImGui::Text("Merry christmas!");
	ImGui::Text("Congratulations on the new year 2023");
}

void Hyko::EToolbar::createEToolbar(int FPS, float dt)
{
	ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar
		| ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Toolbar", nullptr, winFlags);

	ImGui::SetWindowPos({ 0.0f, 0.0f });
	ImGui::SetWindowSize({ Hyko::getWinSize(Window::getNativeWindow()).x, 1});

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Create")) {
			create_Menu();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene data")) {
			scene_Menu();

			ImGui::EndMenu();
		}
#ifdef CHRISTMAS
		if (ImGui::BeginMenu("Christmas")) {
			Christmas();

			ImGui::EndMenu();
		}
#endif // CHRISTMAS

		if (ImGui::BeginMenu("Windows")) {
			ImGui::MenuItem("Debug", nullptr, &debugIsOpen);
			
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();

		if (debugIsOpen) debug(FPS, dt);
	}

	//ImGui::ShowDemoWindow();

	ImGui::End();
}
