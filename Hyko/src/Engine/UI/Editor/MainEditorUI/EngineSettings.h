#pragma once

#include "Engine/Scene/Scene.h"

#include <imgui.h>
#include <memory>

namespace Hyko {
	class ESettings {
	private:
		std::shared_ptr<Scene> m_scene;
	public:
		ESettings() = default;
		ESettings(std::shared_ptr<Scene> scene)
			: m_scene(scene){}
		void init();
	};
}