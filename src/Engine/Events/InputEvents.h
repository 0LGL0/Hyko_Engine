#pragma once
#include <glfw3.h>
#include "../window.h"

namespace Hyko {
	bool isKeyPressed(const Hyko::keyCode keyCode);
	bool isMouseButtonPressed(int mouseButton);

	bool isKeyReleased(int keyCode);
	bool isMouseButtonReleased(int mouseButton);
}