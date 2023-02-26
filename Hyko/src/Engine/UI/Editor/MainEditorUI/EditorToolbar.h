#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/Meshes/Entity.h"

// imgui
#include <imgui.h>
#include <imgui_internal.h>

//std
#include <string>
#include <memory>

//#include "Engine/UI/EngineUILayer.h"

namespace Hyko {
	class EToolbar {
	private:
		friend class EUILayer;

		//std::shared_ptr<Hyko::Entity> m_entity{ new Hyko::Entity{ m_scene } };
		std::shared_ptr<Hyko::Scene> m_scene;
	private:
		bool createIsOpen  = false;
		bool debugIsOpen   = false;
		bool meshLineMode  = false;
		bool meshIsCreting = false;
		bool VSync		   = false;

		float backgroundColor[3]{1.0f, 1.0f, 1.0f};
		int camSpeed = 50.0f;
		int projectionTypeIndx = 0;
	private:
		void scene_Menu();
		void create_Menu();
		void debug(int FPS, float dt);
		void Christmas();
		void settings_Menu();
	public:
		EToolbar() = default;
		EToolbar(std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {};
		~EToolbar() = default;

		void createEToolbar(int FPS, float dt);
	};
}