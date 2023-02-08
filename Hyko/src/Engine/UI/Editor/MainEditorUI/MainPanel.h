#pragma once

#include "GL/Framebuffer.h"

#include "Viewport.h"

#include <memory>

namespace Hyko {
	class EMainPanel {
	private:
		std::shared_ptr<FBO> m_fbo;

		EViewport UI_viewport{m_fbo};
	public:
		EMainPanel(std::shared_ptr<FBO> fbo)
			: m_fbo(fbo){}

		void init();
	};
}