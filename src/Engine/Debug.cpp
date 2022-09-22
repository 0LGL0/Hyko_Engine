#include "Debug.h"
#include "glfw3.h"

void Debug::edgeRenderingOnly(bool state)
{
	switch (state) {
	case true:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case false:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
