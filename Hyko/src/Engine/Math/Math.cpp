#include "Math.h"

// @return translation (glm::vec2), scale (glm::vec2), rotation angle in radians (float) by reference
bool Hyko::Math::decomposeTransformMat(const glm::mat4 matrix, glm::vec2& translate, glm::vec2& scale, float& rot)
{
	auto localMat(matrix);

	if (glm::epsilonEqual(localMat[3][3], 0.0f, glm::epsilon<float>()))
		return false;

	// translate
	translate = glm::vec2(matrix[3][0], matrix[3][1]);
	localMat[3] = glm::vec4(0, 0, 0, localMat[3][3]);

	glm::vec3 Row[3];
	glm::vec3 Pdum3;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			Row[i][j] = localMat[i][j];
	}

	// scale
	scale.x = glm::length(Row[0]);
	Row[0] = glm::detail::scale(Row[0], 1.0f);
	scale.y = glm::length(Row[1]);
	Row[1] = glm::detail::scale(Row[1], 1.0f);

	Pdum3 = glm::cross(Row[1], Row[2]);
	if (dot(Row[0], Pdum3) < 0) {
		for (int i = 0; i < 2; i++) {
			scale[i] *= -1.0f;
			Row[i]	 *= -1.0f;
		}
	}

	// rot 
	rot = atan2(Row[0][1], Row[0][0]);
}