#pragma once

#include "GL/Framebuffer.h"

#include "Viewport.h"
#include "EditorHierarchy.h"
#include "EditorComponentSettings.h"
#include "EngineSettings.h"
#include "Engine/UI/Editor/MainEditorUI/MenuBar/Windows.h"

#include "Engine/Scene/Scene.h"

#include <memory>

namespace Hyko {
	class EMainPanel {
	private:
		std::shared_ptr<FBO> m_fbo;
		std::shared_ptr<Scene> m_scene;

		EViewport m_viewport{ m_fbo, m_scene };
		EHierarchy m_hierarchy{ m_scene };
		EComponentSettings m_componentsSettings{ m_scene };
		ESettings m_engineSettings{ m_scene };
		EWindows m_engineWindows{ m_scene };
	private:
		bool m_engineSettingsEnabled = false;
		bool m_engineDebugEnabled	 = false;
	public:
		EMainPanel(const std::shared_ptr<FBO> fbo, const std::shared_ptr<Scene> scene)
			: m_fbo(fbo), m_scene(scene){}

		void init();
	};
}