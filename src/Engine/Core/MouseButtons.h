#pragma once
#include <stdint.h>

namespace Hyko {
	using mouseButtons = uint16_t;

	namespace Mouse {
		enum : mouseButtons {
			HK_MOUSE_BUTTON_1	   = 0,
			HK_MOUSE_BUTTON_2	   = 1,
			HK_MOUSE_BUTTON_3	   = 2,
			HK_MOUSE_BUTTON_4	   = 3,
			HK_MOUSE_BUTTON_5	   = 4,
			HK_MOUSE_BUTTON_6	   = 5,
			HK_MOUSE_BUTTON_7	   = 6,
			HK_MOUSE_BUTTON_8	   = 7,
			HK_MOUSE_BUTTON_LAST   = HK_MOUSE_BUTTON_8,
			HK_MOUSE_BUTTON_LEFT   = HK_MOUSE_BUTTON_1,
			HK_MOUSE_BUTTON_RIGHT  = HK_MOUSE_BUTTON_2,
			HK_MOUSE_BUTTON_MIDDLE = HK_MOUSE_BUTTON_3,
		};
	}
}