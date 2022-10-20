#pragma once
#include <glm/glm.hpp>

class EProjection {
public:
	glm::vec3 viewProjPos;

	glm::mat4 createViewMatrix(glm::vec3 camPos);
	glm::mat4 createOrthoProjection(float l, float r, float b, float t);
	glm::mat4 resizeOrthoProjection(float width, float height);
};