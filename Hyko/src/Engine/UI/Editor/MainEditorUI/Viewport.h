#pragma once

#include "GL/Framebuffer.h"
#include "Engine/Scene/Scene.h"

#include <memory>

namespace Hyko {
	class EViewport {
	private:
		std::shared_ptr<FBO> m_fbo;
		std::shared_ptr<Scene> m_scene;
	private:
		void secondUILayer();
	public:
		EViewport(std::shared_ptr<FBO> fbo, std::shared_ptr<Scene> scene)
			: m_fbo(fbo), m_scene(scene) {}

		void init();
	};
}