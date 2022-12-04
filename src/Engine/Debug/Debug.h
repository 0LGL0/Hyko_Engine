#pragma once

#include <glfw3.h>

namespace Hyko {
	void setVSync(bool is);
	void edgeRenderingLineOnly(bool is);

	int getFPS(float dt);
}