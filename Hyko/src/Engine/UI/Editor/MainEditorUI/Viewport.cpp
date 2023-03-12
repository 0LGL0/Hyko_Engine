#include "Viewport.h"
#include "Engine/Scene/Camera/EditorCamera.h"

#include <imgui.h>

void Hyko::EViewport::viewportMenuBar()
{
	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove;

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100);
	if (ImGui::Button("##ViewportArrow", ImVec2(20.0f, 20.0f))) 
		ImGui::OpenPopup("ViewportArrowMenu");
	ImGui::PopStyleVar();

	if (ImGui::BeginPopup("ViewportArrowMenu", flags)) {
		static int camSpeed = 20;
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Camera speed");
		ImGui::SameLine();
		if (ImGui::SliderInt("##CamSpeed", &camSpeed, 20, 300)) {
			camSpeed = (camSpeed / 20) * 20;
			m_scene->editCamera.setCameraSpeed(camSpeed);
		}

		ImGui::EndPopup();
	}
}

void Hyko::EViewport::init()
{
	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_MenuBar;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Viewport", nullptr, winFlags);
	ImGui::PopStyleVar();
	m_fbo->setFramebufferWidth(ImGui::GetWindowSize().x);
	m_fbo->setFramebufferHeight(ImGui::GetWindowSize().y);
	ECamera::Resize(m_fbo->getFramebufferWidth(), m_fbo->getFramebufferHeight());

	ImGui::Image((void*)m_fbo->getFBOTexture(), { (float)m_fbo->getFramebufferWidth(), (float)m_fbo->getFramebufferHeight() }, {0, 1}, {1, 0});

	if (ImGui::BeginMenuBar()) {
		viewportMenuBar();

		ImGui::EndMenuBar();
	}

	ImGui::End();
}
