#include "EngineSettings.h"

void ESetting::init()
{
	auto viewport = ImGui::GetMainViewport();

	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::SetNextWindowSize(viewport->Size);

	if (ImGui::Begin("Engine settings")) {
		

		ImGui::End();
	}
}
