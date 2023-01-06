#include "EditorComponentSettings.h"

void Hyko::EComponentSettings::createComponentSettings()
{
	ImGui::Begin("Component settings");

	ImGui::InputInt("Indx", &indxSelecting);

	if (indxSelecting > (m_scene->sceneTriangles.size() - 1))
		indxSelecting = (m_scene->sceneTriangles.size() - 1);

	if (!m_scene->sceneTriangles.empty()) {
		ImGui::DragFloat2("Position", glm::value_ptr(m_scene->sceneTriangles[indxSelecting].m_position), 0.01f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat2("Scale", glm::value_ptr(m_scene->sceneTriangles[indxSelecting].m_scale), 0.01f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("Rotation", &m_scene->sceneTriangles[indxSelecting].m_rotation, 0.01f, 0.0f, FLT_MAX);
		ImGui::ColorEdit4("Color", glm::value_ptr(m_scene->sceneTriangles[indxSelecting].m_color));
	}

	ImGui::End();
}
