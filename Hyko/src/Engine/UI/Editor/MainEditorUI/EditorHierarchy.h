#pragma once

#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity/Entity.h"

// imgui
#include <imgui.h>

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

		Entity m_selectedEntity;
	private:
		void createNewTree(Entity entity);
	public:
		EHierarchy() = default;
		EHierarchy(const std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {}
		~EHierarchy() = default;

		void init();
	};
}