#pragma once

#include "GL/Window/window.h"
#include "Engine/System/Time.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Meshes/Entity.h"

// UI panels
#include "Editor/MainEditorUI/EditorToolbar.h"
#include "Editor/MainEditorUI/EditorComponentSettings.h"
#include "Editor/MainEditorUI/EditorHierarchy.h"

// GL
#include <glfw3.h>

// std
#include <memory>

namespace Hyko {
	class EUILayer {
	private:
		std::shared_ptr<Hyko::Scene> m_scene;
		std::shared_ptr<Hyko::Entity> m_entity{ new Hyko::Entity{m_scene} };

		Hyko::EToolbar eToolbar{ m_scene, m_entity };
		Hyko::EHierarchy eHierarchy{ m_scene };
		Hyko::EComponentSettings eCompSettings{ m_scene };
	private:
		float m_LastFrameTime = 0.0f;
	public:
		EUILayer() = default;
		EUILayer(std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {};
		~EUILayer();

		void createUILayer(GLFWwindow *window);
		void OnUpdate(Time dt);
		void renderEnities();
		void newFrame();
		void Render();
	};
}