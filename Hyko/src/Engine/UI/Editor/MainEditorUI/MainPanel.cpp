#include "MainPanel.h"

#include "Engine/Events/InputEvents.h"

#include <imgui.h>

void Hyko::EMainPanel::fileMenu()
{
	static bool newProjEnabled = false;
	static bool openProjEnabled = false;
	static bool newSceneEnabled = false;
	static bool openSceneEnabled = false;
	static bool saveCurrEnabled = false;
	static bool saveCurrAsEnabled = false;
	static bool saveAllEnabled = false;
	static bool buildProjectEnabled = false;

	if (ImGui::BeginMenu("File")) {
		if (ImGui::BeginMenu("Project")) {
			ImGui::MenuItem("New project", "Ctrl + N", &newProjEnabled);
			ImGui::MenuItem("Open project", "Ctrl + O", &openProjEnabled);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene")) {
			ImGui::MenuItem("New Scene", "Ctrl + Alt + N", &newSceneEnabled);
			ImGui::MenuItem("Open Scene", "Ctrl + Alt + O", &openSceneEnabled);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Save")) {
			ImGui::MenuItem("Save current", "Ctrl + S", &saveCurrEnabled);
			ImGui::MenuItem("Save current as", "Ctrl + Alt + S", &saveCurrAsEnabled);
			ImGui::MenuItem("Save all", "Ctrl + Shift + S", &saveAllEnabled);

			ImGui::EndMenu();
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Build project for Windows", "Ctrl + B")) {
			// In subsequent updates
		}

		ImGui::EndMenu();
	}
}

void Hyko::EMainPanel::editMenu()
{
	static bool projSettingsEnabled	  = false;
	static bool engineSettingsEnabled = false;

	if (ImGui::BeginMenu("Edit")) {
		ImGui::MenuItem("Undo", "Ctrl + Z");
		ImGui::MenuItem("Redo", "Ctrl + Shift + Z");

		ImGui::Separator();

		ImGui::MenuItem("Engine settings", "Ctrl + Shift + O", &engineSettingsEnabled);
		ImGui::MenuItem("Project settings", "Ctrl + Shift + Alt + O", &projSettingsEnabled);

		ImGui::EndMenu();
	}

	// Keyboard shortcuts ---------------------------
	if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_SHIFT) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_SHIFT))
		&& (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_ALT) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_ALT))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_O)))
		projSettingsEnabled = true;

	else if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_SHIFT) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_SHIFT))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_O)))
		engineSettingsEnabled = true;
	// ----------------------------------------------

	if (engineSettingsEnabled)
		m_engineSettings.init();
}

void Hyko::EMainPanel::windowsMenu()
{
	static bool debugEnabled	  = false;
	static bool terminalEnabled   = false;
	static bool outLogEnabled	  = false;
	static bool msgLogEnabled	  = false;

	if (ImGui::BeginMenu("Windows")) {
		ImGui::MenuItem("Debug", "Ctrl + Shift + D", &debugEnabled);
		ImGui::MenuItem("Terminal", "Ctrl + T", &terminalEnabled);
		ImGui::MenuItem("Output log", "Ctrl + L", &outLogEnabled);
		ImGui::MenuItem("Message log", "Ctrl + Shift + L", &msgLogEnabled);

		ImGui::EndMenu();
	}

	// Keyboard shortcuts ---------------------------
	if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_SHIFT) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_SHIFT))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_D)))
		debugEnabled = true;

	else if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_T)))
		terminalEnabled = true;

	else if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_L)))
		outLogEnabled = true;

	else if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_SHIFT) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_SHIFT))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_L)))
		msgLogEnabled = true;
	// ----------------------------------------------

	if (debugEnabled)
		m_engineWindows.DebugMenu();
}

void Hyko::EMainPanel::helpMenu()
{
	if (ImGui::BeginMenu("Help")) {
		// TODO: Help options

		ImGui::EndMenu();
	}

	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Coming soon");
}

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

		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockFlags);

		if (ImGui::BeginMenuBar()){
			fileMenu();
			editMenu();
			windowsMenu();
			helpMenu();

			ImGui::EndMenuBar();
		}

		m_viewport.init(m_scene->m_selectedEntities);
		m_hierarchy.init();
		m_componentsSettings.init(m_scene->m_selectedEntities);
		m_engineContentBrowser.init();

		ImGui::End();
	}
}
