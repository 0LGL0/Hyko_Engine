#pragma once

#include "EditorToolbar.h"
#include "EditorHierarchy.h"
#include "EditorComponentSettings.h"

namespace Hyko {
	class EUI {
	private:
		Hyko::EToolbar eToolbar;
		Hyko::EHierarchy eHierarchy;
		Hyko::EComponentSettings eCompSettings;
	public:
		void createEditorUI();

		bool mashIsCreated(int8_t type);
	};
}