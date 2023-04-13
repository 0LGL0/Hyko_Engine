#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Hyko {
	namespace Math{
		bool decomposeTransformMat(const glm::mat4 matrix, glm::vec2& translate, glm::vec2& scale, float& rot);
	}
}