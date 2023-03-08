#include "EngineSettings.h"

#include "Engine/System/FileSystem/LogFiles.h"
#include "Engine/UI/EngineFonts.h"
#include "Engine/UI/EngineUILayer.h"
#include "Engine/System/Debug/Log.h"

#define USE_BOOKMARK
#include <ImGuiFileDialog/ImGuiFileDialog.h>

void Hyko::ESettings::Data()
{
	ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;

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

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	ImGui::InputText("##LogsPath", &LogF::m_folderPath, flags); // The path to the logs folder

	ImGui::SameLine();

	if (ImGui::Button("##OpenFolder", ImVec2(ImGui::GetItemRectSize().y, ImGui::GetItemRectSize().y))) {
		ImGuiFileDialogFlags dialogFlags = ImGuiFileDialogFlags_DontShowHiddenFiles | ImGuiFileDialogFlags_DisableBookmarkMode;

		ImGuiFileDialog::Instance()->OpenDialog("PathToLogsKey", "Path to logs", nullptr, ".");
	}

	ImGui::PopStyleVar();

	if (ImGuiFileDialog::Instance()->Display("PathToLogsKey"))
	{
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();

			if (filePathName != "")
				LogF::editFolderPath(filePathName);
		}
		
		ImGuiFileDialog::Instance()->Close();
	}
}

void Hyko::ESettings::init()
{
	auto &io = ImGui::GetIO();

	ImGuiTextFilter filterSettings;

	static const float filterWidth = 300.0f;

	//static float HierarchyWinWidth; // left window width
	//static float ElementSettingsWidth; // right window width

	const ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_SpanAvailWidth;

	ImGui::SetNextWindowBgAlpha(1.0f);
	//ImGui::SetNextWindowSize(io.DisplaySize);

	ImGui::Begin("Engine settings");

	/*HierarchyWinWidth = ImGui::GetWindowContentRegionWidth() / 8.0f;
	ElementSettingsWidth = ImGui::GetWindowContentRegionWidth() - HierarchyWinWidth;*/

	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetWindowContentRegionWidth() - filterWidth));

	ImGui::Text("Find");
	ImGui::SameLine();
	filterSettings.Draw("##EngineSettingsFilter", filterWidth);

	ImGui::SetCursorPosX(0.0f);

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
		ImGui::PushFont(Font::HeaderFont);
		if (ImGui::TreeNodeEx(m_HierarchySectionNames[i][0], treeFlags)) {
			ImGui::PushFont(Font::BaseFont);

			for (int j = 1; j <= m_HierarchySectionNames.size(); j++) {
				if (ImGui::Selectable(m_HierarchySectionNames[i][j]))
					m_selectedSectionName = (char*)m_HierarchySectionNames[i][j];
			}

			ImGui::PopFont();

			ImGui::TreePop();
		}

		ImGui::PopFont();
	}

	ImGui::NextColumn();

	if (m_selectedSectionName != nullptr) {
		if (filterSettings.PassFilter("Clear all data"))
			if (m_selectedSectionName == "Data") Data();
	}

	ImGui::Columns(1);

	ImGui::End();
}
