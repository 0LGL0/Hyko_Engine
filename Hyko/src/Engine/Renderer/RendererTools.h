#pragma once

#include "Engine/Buffers/OpenGL/VO.h"

#include <vector>

namespace Hyko {
	class RendererTools {
	private:
		VO m_vo;
	public:
		void renderIndxes(std::vector<unsigned int> indxes);

		void createVO(std::vector<float> vertices, std::vector<unsigned int> indices);
	public: // getters
		VO getVO() const { return m_vo; }
	};
}