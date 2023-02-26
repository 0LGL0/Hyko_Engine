#include "UIFunctions.h"

bool HykoUI::HierarchyEntityMenu(std::shared_ptr<Hyko::Scene> scene, HykoHierarchyEntityMenuConfig flags) {
	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::Button("Create entity")) {
			Hyko::Entity entity = scene->addToScene();
			const int entt = entity;

			entity.addComponent<Hyko::TagComponent>().Tag = ("Entity" + std::to_string(entity));
			entity.addComponent<Hyko::TransformComponent>().Transform = glm::mat4(1.0f);

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
		return true;
	}

	return false;
}