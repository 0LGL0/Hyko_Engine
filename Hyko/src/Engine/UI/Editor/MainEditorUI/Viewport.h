#pragma once

#include "GL/Framebuffer.h"

#include <memory>

namespace Hyko {
	class EViewport {
	private:
		std::shared_ptr<FBO> m_fbo;
	public:
		EViewport(std::shared_ptr<FBO> fbo)
			: m_fbo(fbo){}

		void init();
	};
}