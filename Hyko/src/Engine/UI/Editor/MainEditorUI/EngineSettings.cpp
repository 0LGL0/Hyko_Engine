#include "EngineSettings.h"

#include "Engine/System/FileSystem/LogFiles.h"


void Hyko::ESettings::Data()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Clear all data"))
		Hyko::LogF::deleteAllLogs();

	ImGui::SameLine();

	// TODO: In the future, replace the button with an ImageButton with arrow texture
	if (ImGui::Button("##DataArrow", ImVec2(ImGui::GetItemRectSize().y, ImGui::GetItemRectSize().y))) { // Arrow to expand other methods to clear data
		ImGui::OpenPopup("##DataMetods");
	}
	ImGui::PopStyleVar();

	if (ImGui::BeginPopup("##DataMetods")) {
		if (ImGui::Selectable("Clear only all logs")) 
			Hyko::LogF::deleteAllLogs();

		if (ImGui::Selectable("Clear cache")) {
			// Clear cache code...
		}

		// And others methodes (maybe)

		ImGui::EndPopup();
	}
}

void Hyko::ESettings::init()
{
	auto &io = ImGui::GetIO();

	ImGuiTextFilter filterSettings;
	ImGuiTextFilter filterHierarchy;

	bool m_settingsWinEnabled = false;

	static const float filterWidth = 300.0f;

	static float HierarchyWinWidth; // left window width
	static float ElementSettingsWidth; // right window width

	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_None;
	const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;

	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Engine settings", nullptr, winFlags);

	HierarchyWinWidth = ImGui::GetWindowContentRegionWidth() / 8.0f;
	ElementSettingsWidth = ImGui::GetWindowContentRegionWidth() - HierarchyWinWidth;

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetWindowContentRegionWidth() - filterWidth));

	ImGui::Text("Find");
	ImGui::SameLine();
	filterSettings.Draw("##EngineSettingsFilter", filterWidth);

	ImGui::SameLine();
	ImGui::SetCursorPosX(0.0f);
	
	filterHierarchy.Draw("##EngineHierarchySettingsFilter", 50.0f);

	ImGui::Separator();

	ImGui::Columns(2, "##EngineSettingsColumns");

	/*if (ImGui::TreeNode("System")) {
		if (ImGui::Selectable("Data"))
			SystemDataOpened = true;
		else
			SystemDataOpened = false;
		ImGui::TreePop();
	}*/

	for (int i = 0; i < m_HierarchySectionNames.size(); i++) {
		ImGui::Text(m_HierarchySectionNames[i][0]);
		
		for (int j = 1; j <= m_HierarchySectionNames.size(); j++) {
			if (filterHierarchy.PassFilter(m_HierarchySectionNames[i][j])) {
				ImGui::SetCursorPosX(20.0f);

				if (ImGui::Selectable(m_HierarchySectionNames[i][j])) {
					m_selectedSectionName = (char*)m_HierarchySectionNames[i][j];
				}

				ImGui::SetCursorPosX(0.0f);
			}
		}
	}

	ImGui::NextColumn();

	if (m_selectedSectionName != nullptr) {
		if (m_selectedSectionName == "Data") Data();
	}

	ImGui::Columns(1);

	ImGui::End();
}
