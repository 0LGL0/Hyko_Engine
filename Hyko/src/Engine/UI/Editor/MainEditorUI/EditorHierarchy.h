#pragma once

#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity/Entity.h"

// imgui
#include <imgui.h>
#include <imgui_internal.h>

#include <entt.hpp>

// std
#include <string>
#include <memory>

namespace Hyko {
	class EHierarchy{
	private:
		std::shared_ptr<Hyko::Scene> m_scene;
		friend class Scene;
		friend class EMainPanel;

		bool m_isMovingToMainBranch = false; // it's variable takes the value true when the mouse cursor with the dragged entity is hovered over the window
		uint32_t m_draggedEntity = -1;
	private:
		void createNewTree(Entity entity);
		void copingEntity();
		void rightClickItemMenu(const Hyko::Entity entity);
		void rightClickWindowMenu(const ImGuiPopupFlags popupFlags);
		void deleteEntity();
	public:
		EHierarchy() = default;
		EHierarchy(const std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {}
		~EHierarchy() = default;

		void init();
	};
}