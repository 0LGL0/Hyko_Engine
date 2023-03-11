#pragma once

#include <imgui.h>
#include <imgui_internal.h>

namespace Hyko {
	class EContentBrowser {
	private:
		void windowRightClickMenu();
		void itemRightClickMenu();
	public:
		void init();
	};
}