#pragma once

#include "Engine/Scene/Scene.h"

#include <imgui.h>

namespace Hyko {
	class EWindows {
	private:
		std::shared_ptr<Scene> m_scene;
	public:
		EWindows(std::shared_ptr<Scene> scene)
			: m_scene(scene) {}

		void DebugMenu();
	};
}