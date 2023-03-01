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
		ImGui::PopStyleVar();

		ImGuiIO& io = ImGui::GetIO();
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockFlags);

		if (ImGui::BeginMenuBar()){

			if (ImGui::BeginMenu("File")) {
				// TODO: File options

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit")) {
				// TODO: Edit options

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help")) {
				// TODO: Help options

				ImGui::EndMenu();
			}

			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Coming soon");

			ImGui::EndMenuBar();
		}

		m_viewport.init();
		m_hierarchy.init();
		m_componentsSettings.init(m_hierarchy.m_selectedEntity);

		ImGui::End();
	}
}
