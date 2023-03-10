#include "Windows.h"

#include "GL/Window/window.h"
#include "Engine/System/Time.h"

#include <vector>

void Hyko::EWindows::DebugMenu()
{
	static bool systemEnabled = true;
	static bool sceneEnabled  = false;

	ImGui::Begin("Debug");
	if (ImGui::BeginCombo("Debug type", "")) {
		if (ImGui::Selectable("System")) {
			systemEnabled = true;
			sceneEnabled = false;
		}

		else if (ImGui::Selectable("Scene")) {
			sceneEnabled = true;
			systemEnabled = false;
		}

		ImGui::EndCombo();
	}

	if (systemEnabled) {
		ImGui::Text("FPS: %d", Window::getFPS(Scene::getTime().getDeltaMilliseconds()));
		ImGui::Text("Delta milliseconds: %.6f", Scene::getTime().getDeltaMilliseconds());
		ImGui::Text("Delta seconds: %.8f", Scene::getTime().getDeltaSeconds());
	}

	else if (sceneEnabled) {
		ImGui::Text("Triangles count: %d", m_scene->getEntityCount());
	}

	ImGui::End();
}
