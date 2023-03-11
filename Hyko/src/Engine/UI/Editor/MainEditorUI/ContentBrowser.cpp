#include "ContentBrowser.h"

void Hyko::EContentBrowser::windowRightClickMenu()
{
	bool createClicked = false;
	static bool menuEnabled = false;

	if (ImGui::BeginMenu("Create")) {
		if (ImGui::BeginMenu("Basic")) {
			if (ImGui::Selectable("New folder")) {
				// In the next update
			}

			if (ImGui::Selectable("New C++ script")) {
				// In the next update
			}

			if (ImGui::Selectable("New prefab")) {
				// In the next update
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Material | Texture")) {
			if (ImGui::Selectable("New material")) {
				// In the next update
			}

			if (ImGui::Selectable("New texture")) {
				// In the next update
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}
}

void Hyko::EContentBrowser::itemRightClickMenu()
{
	if (ImGui::Selectable("Delete")) {
		// In the next update
	}

	if (ImGui::Selectable("Rename")) {
		// In the next update
	}

	if (ImGui::Selectable("Set color")) {
		// In the next update
	}

	if (ImGui::Selectable("Favourite")) { // cannot delete this element
		// In the next update
	}

	if (ImGui::Selectable("Show in explorer")) {
		// In the next update
	}
}

void Hyko::EContentBrowser::init()
{
	ImGuiTextFilter ContentBrowserFilter;
	ImGuiTextFilter HierarchyFilter;

	static float filesViewerWidth = 250.0f;
	static int folderSize = 2;

	static bool filesViewerEnable = false;

	bool buttonClicked = false; // files viewer button

	ImGui::Begin("Content browser");

	//											Size of Filter
	if (ImGui::Button("##FilesViewer", ImVec2(ImGui::GetItemRectSize().y, ImGui::GetItemRectSize().y))) { // TODO: replace button with ImageButton
		buttonClicked = true;
		if (!filesViewerEnable)
			filesViewerEnable = true;
		else
			filesViewerEnable = false;
	}

	ImGui::SameLine();

	if (!filesViewerEnable) {
		// content filter
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Search");
		ImGui::SameLine();
		ContentBrowserFilter.Draw("##ContentBrowserFilter", ImGui::GetWindowContentRegionWidth() - (ImGui::GetFontSize() * 6)); // 6 - the number of letters in the word "Search"
	}
		
	if (filesViewerEnable) {
		ImGui::BeginColumns("##ContentBrowserColumns", 2);
		if(buttonClicked)
			ImGui::SetColumnWidth(0, filesViewerWidth + 2.0f); // 2.0f - offset

		// Hierarchy -----------------------------------------------------------------------------
		// Hierarchy filter
		ImGui::SameLine();
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Search");
		ImGui::SameLine();
		HierarchyFilter.Draw("##HierarchyFilter", ImGui::GetColumnWidth(0) - (ImGui::GetFontSize() * 6)); // 6 - the number of letters in the word "Search"

		ImGui::Text("In the next update)");

		//-----------------------------------------------------------------------------------------

		if (ImGui::GetColumnWidth(0) <= ImGui::GetWindowContentRegionWidth() / 8.0f)
			ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionWidth() / 8.0f);

		ImGui::NextColumn();

		// Content filter
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Search");
		ImGui::SameLine();
		ContentBrowserFilter.Draw("##ContentBrowserFilter", ImGui::GetColumnWidth(1) - (ImGui::GetFontSize() * 6)); // 6 - the number of letters in the word "Search"
	}
		
	ImGui::Text("In the next update)");

	if (ImGui::BeginPopupContextItem("##ItemRightClickMenu")) {
		itemRightClickMenu();
		ImGui::EndPopup();
	}

	if (ImGui::BeginPopupContextWindow("WindowRightClickMenu", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight)) {
		windowRightClickMenu();
		ImGui::EndPopup();
	}

	if (filesViewerEnable) {
		filesViewerWidth = ImGui::GetColumnWidth(0);
		ImGui::EndColumns();
	}

	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionWidth() - 22.0f, ImGui::GetWindowContentRegionMax().y - 22.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100.0f);
	if (ImGui::Button("##ContentBrowserArrowMenu", ImVec2(20.0f, 20.0f))) // in the future, replace button with imageButton
		ImGui::OpenPopup("ContentBrowserMenu");
	ImGui::PopStyleVar();

	if (ImGui::BeginPopup("ContentBrowserMenu", ImGuiWindowFlags_NoMove)) {

		if (ImGui::SliderInt("##FolderSize", &folderSize, 1, 5)) {
			// In the next update
		}

		ImGui::EndPopup();
	}

	ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));

	ImGui::End();
}
