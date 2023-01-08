#include "Debug.h"

// GL
#include <glfw3.h>

void Hyko::edgeRenderingLineOnly(bool is)
{
	switch (is) {
	case true:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case false:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
}

int Hyko::getFPS(float milliSeconds)
{
	return static_cast<int>(1000.0f / milliSeconds);
}
