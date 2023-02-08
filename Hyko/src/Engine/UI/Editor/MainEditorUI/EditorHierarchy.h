#pragma once

#include "Engine/Scene/Scene.h"

// imgui
#include <imgui.h>

// std
#include <string>
#include <memory>

namespace Hyko {
	class EHierarchy{
	private:
		std::shared_ptr<Hyko::Scene> m_scene;
	private:
		void createNewTree(int8_t type, int indx);
	public:
		EHierarchy() = default;
		EHierarchy(std::shared_ptr<Hyko::Scene> &scene)
			: m_scene(scene) {}
		~EHierarchy() = default;

		void createHierarchy();
	};
}