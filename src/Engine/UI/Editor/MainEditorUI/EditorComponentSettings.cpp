#include "EditorComponentSettings.h"
#include "../Engine/Scene/Scene.h"

extern Hyko::Scene scene;
extern Hyko::Entity entity;

void Hyko::EComponentSettings::createComponentSettings()
{
	ImGui::Begin("Component settings");

	ImGui::InputInt("Indx", &indxSelecting);

	if (indxSelecting > (scene.sceneTriangles.size() - 1))
		indxSelecting = (scene.sceneTriangles.size() - 1);

	if (!scene.sceneTriangles.empty()) {
		ImGui::DragFloat2("Position", glm::value_ptr(scene.sceneTriangles[indxSelecting].m_position), 0.01f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat2("Scale", glm::value_ptr(scene.sceneTriangles[indxSelecting].m_scale), 0.01f, -FLT_MAX, FLT_MAX);
		ImGui::DragFloat("Rotation", &scene.sceneTriangles[indxSelecting].m_rotation, 0.01f, 0.0f, FLT_MAX);
		ImGui::ColorEdit4("Color", glm::value_ptr(scene.sceneTriangles[indxSelecting].m_color));
	}

	ImGui::End();
}
