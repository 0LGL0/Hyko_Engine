#include "UI.h"
#include "../Engine/Core/Hyko.h"

void Hyko::EUI::createEditorUI()
{
	eToolbar.createEToolbar();
	eHierarchy.createHierarchy();
	eCompSettings.createComponentSettings();
}

bool Hyko::EUI::mashIsCreated(int8_t type)
{
	if (type == HK_TRIANGLE)
		return eToolbar.meshIsCreting;
}
