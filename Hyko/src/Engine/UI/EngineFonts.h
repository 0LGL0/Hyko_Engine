#pragma once

#include <imgui.h>

using HKFont = ImFont;

namespace Hyko {
	struct Font {
		static HKFont* BaseFont;	// A font that is used almost everywhere
		static HKFont* HeaderFont;	// A font that is used in the headers
	};
}