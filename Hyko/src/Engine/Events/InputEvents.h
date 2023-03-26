#pragma once

// input
#include "Engine/Core/KeyKodes.h"
#include "Engine/Core/MouseButtons.h"

#include "GL/Window/window.h"

// GL
#include <glfw3.h>

// GL / Maths
#include <glm/glm.hpp>

namespace Hyko {
	namespace Input {
		static float m_mousePosX = 0.0f;
		static float m_mousePosY = 0.0f;
		static float m_xOffset = 0.0;
		static float m_yOffset = 0.0;
		static int m_keyAction = 0;
		static int m_buttonAction = 0;
		static int m_key = -1;

		static bool m_scrollCallbackIs = false;

		static Hyko::keyCode m_pressedKey = Hyko::Key::HK_KEYBOARD_NONE;

		static long int m_pressTime = 0;

		void resetInput();

		bool isKeyPressed(const Hyko::keyCode keyCode);
		bool isMouseButtonPressed(const Hyko::mouseButtons mouseButton);

		bool isKeyReleased(const Hyko::keyCode keyCode);
		bool isMouseButtonReleased(const Hyko::mouseButtons mouseButton);

		bool isKeyReleasedAfterPress(const Hyko::keyCode keyCode, const bool repeat = true);

		// getters
		glm::vec2 getMousePos();

		float getMouseXOffset();
		float getMouseYOffset();

		// setters
		void setMouseXOffset(float value);
		void setMouseYOffset(float value);

		void setMouseXPos(float value);
		void setMouseYPos(float value);
	}
}