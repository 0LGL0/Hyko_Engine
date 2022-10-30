#pragma once
#include <glm/glm.hpp>

class EProjection {
private:
	glm::vec3 editorCameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	glm::vec3 getEditorCameraPosition(){ return editorCameraPosition; };

	void setEditorCameraPosition(glm::vec3 newPos) { editorCameraPosition = newPos; };
	void setEditorCameraPosition(float x, float y, float z) { editorCameraPosition.x = x;  editorCameraPosition.y = y; editorCameraPosition.z = z; };

	glm::mat4 createViewMatrix();
	glm::mat4 createOrthoProjection(float l, float r, float b, float t);
	glm::mat4 resizeOrthoProjection(float width, float height);
};