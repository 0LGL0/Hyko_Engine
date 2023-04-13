#pragma once

#include "Engine/Buffers/OpenGL/Framebuffer.h"
#include "Engine/Scene/Scene.h"

//imgui
#include <imgui.h>

// imguizmo
#include <ImGuizmo.h>

#include <memory>

namespace Hyko {
	class EViewport {
	private:
		std::shared_ptr<FBO> m_fbo;
		std::shared_ptr<Scene> m_scene;

		ImGuizmo::OPERATION m_gizmoOperation = ImGuizmo::TRANSLATE_X | ImGuizmo::TRANSLATE_Y;
		ImGuizmo::MODE m_gizmoMode			 = ImGuizmo::WORLD;
	private:
		void viewportMenuBar();
		void gizmo(const std::set<uint32_t> selectedEntities);
	public:
		EViewport(std::shared_ptr<FBO> fbo, std::shared_ptr<Scene> scene)
			: m_fbo(fbo), m_scene(scene) {}

		void init(const std::set<uint32_t> selectedEntities);
	};
}