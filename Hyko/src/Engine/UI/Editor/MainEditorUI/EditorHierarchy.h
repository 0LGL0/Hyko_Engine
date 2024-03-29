#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity/Entity.h"

// imgui
#include <imgui.h>
#include <imgui_internal.h>

#include <entt.hpp>

// std
#include <memory>

namespace Hyko {
	class EHierarchy{
	private:
		std::shared_ptr<Hyko::Scene> m_scene;
		friend class Scene;
		friend class EMainPanel;
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