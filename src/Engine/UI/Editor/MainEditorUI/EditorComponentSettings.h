#pragma once
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "EditorHierarchy.h"
#include "EditorToolbar.h"

namespace Hyko {
	class EComponentSettings : private Hyko::EHierarchy, EToolbar{
	private:
		float pos[2]{0.0f, 0.0f};
		float scale[2]{1.0f, 1.0f};

		int indxSelecting = 0;
	public:
		void createComponentSettings();
	};
}