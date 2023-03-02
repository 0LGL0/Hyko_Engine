#include "EngineSettings.h"

void Hyko::ESettings::init()
{
	auto &io = ImGui::GetIO();

	ImGuiTextFilter filter;

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
	filter.Draw("##EngineSettingsFilter", filterWidth);

	ImGui::SetCursorPosX(0.0f);
	ImGui::Separator();

	ImGui::Columns(2, "##EngineSettingsColumns");
	
	// Text filter ******************************************************************
	if (filter.PassFilter("Basic")) {
		if (ImGui::TreeNodeEx("Basic", treeFlags)) {

			ImGui::TreePop();
		}
	}

	ImGui::NextColumn();

	ImGui::Text("Test");

	ImGui::Columns(1);

	ImGui::End();
}
