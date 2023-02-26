#pragma once

#include "Engine/Scene/Entity/Entity.h"
#include "Engine/Scene/Scene.h"

#include <imgui.h>
#include <glm/glm.hpp>
#include <memory>

using HykoComponentsMenuConfig		= int;
using HykoHierarchyEntityMenuConfig = int;

enum HykoMenuConfig_ {
	HykoComponentsMenuConfig_None = 0,
	HykoComponentsMenuConfig_DeleteComponent = 1
};

enum HykoHierarchyEntityMenuConfig_ {
	HykoHierarchyEntityMenuConfig_None = 0
};

namespace HykoUI {
	template<typename T>
	bool ComponentsMenu(Hyko::Entity entity, const HykoComponentsMenuConfig flags)
	{
		if (ImGui::BeginPopupContextItem()) {
			if (flags & HykoComponentsMenuConfig_DeleteComponent) {
				if (ImGui::Button("Delete component")) {
					entity.deleteComponent<T>();

					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
			return true;
		}

		return false;
	}

	bool HierarchyEntityMenu(std::shared_ptr<Hyko::Scene> scene, HykoHierarchyEntityMenuConfig flags = 0);

}