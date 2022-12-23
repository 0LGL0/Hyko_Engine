#pragma once
#include <glm/glm.hpp>

namespace Hyko {
	struct Triangle{
	public:
		static int count;
		int indx = 0;

		int8_t type;

		glm::vec2 m_position = { 0.0f, 0.0f };
		glm::vec2 m_scale	 = { 1.0f, 1.0f };
		glm::vec4 m_color	 = { 1.0f, 1.0f, 1.0f, 1.0f };

		float m_rotation = 0.0f;
	};
}