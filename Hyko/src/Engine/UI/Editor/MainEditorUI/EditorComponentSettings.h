#pragma once

// UI
#include "EditorHierarchy.h"
#include "EditorToolbar.h"

#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity/Entity.h"

// imgui
#include <imgui.h>
#include <imgui_stdlib.h>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <memory>

namespace Hyko {
	class EComponentSettings{
	private:
		std::shared_ptr<Hyko::Scene> m_scene;

		friend class TagComponent;
	private:
		glm::vec2 translate;
		glm::vec2 scale;
		float rotation;

		bool addComponentButton = false;
		bool circleIsSelected = false;
	private:
		void TagComponent(Entity entity, const ImGuiTreeNodeFlags flags);
		void TransformComponent(Entity entity, const ImGuiTreeNodeFlags flags);
		void SpriteComponent(Entity entity, const ImGuiTreeNodeFlags flags);
		void ComponentsFilter(Entity entity);
	public:
		EComponentSettings() = default;
		EComponentSettings(std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {};

		void init(Entity entity);
	};
}