#pragma once

// UI
#include "EditorHierarchy.h"
#include "EditorToolbar.h"

#include "../Engine/Scene/Scene.h"

// imgui
#include <imgui.h>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <memory>

namespace Hyko {
	class EComponentSettings : private Hyko::EHierarchy, EToolbar{
	private:
		std::shared_ptr<Hyko::Scene> m_scene;
	private:
		int indxSelecting = 0;
	public:
		EComponentSettings() = default;
		EComponentSettings(std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {};

		void createComponentSettings();
	};
}