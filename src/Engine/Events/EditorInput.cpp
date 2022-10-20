#include "EditorInput.h"
#include "../Engine/Projection/EditorProjection.h"
#include <glm/gtc/matrix_transform.hpp>

EProjection eProj;

glm::vec3 EInput::EditorCameraControl(char key)
{
	glm::vec3 newCamPos = glm::vec3(0.0f, 0.0f, 0.0f);

	switch (key) {
	case 'w':
		newCamPos.y = eProj.viewProjPos.y + 0.1f;
		break;
	case 's':
		newCamPos.y = eProj.viewProjPos.y - 0.1f;
		break;
	case 'd':
		newCamPos.x = eProj.viewProjPos.y + 0.1f;
		break;
	case 'a':
		newCamPos.x = eProj.viewProjPos.y - 0.1f;
		break;
	}

	eProj.viewProjPos = newCamPos;

	return newCamPos;
}
