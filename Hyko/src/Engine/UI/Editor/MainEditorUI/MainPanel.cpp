#include "MainPanel.h"

#include <imgui.h>

void Hyko::EMainPanel::init()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);

	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNavFocus
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_MenuBar;

	const ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_None;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	if (ImGui::Begin("Main", nullptr, winFlags)) {
		ImGuiIO& io = ImGui::GetIO();
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockFlags);

		m_viewport.init();
		m_hierarchy.init();
		m_componentsSettings.init(m_hierarchy.m_selectedEntity);

		ImGui::End();
	}
	ImGui::PopStyleVar();
}
