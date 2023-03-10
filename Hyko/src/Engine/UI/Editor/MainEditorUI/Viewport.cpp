#include "Viewport.h"
#include "Engine/Scene/Camera/EditorCamera.h"

#include <imgui.h>

void Hyko::EViewport::secondUILayer()
{
	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollWithMouse
		| ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDocking;

	auto& style = ImGui::GetStyle();

	//ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x, ImGui::GetItemRectMin().y));

	if (ImGui::Begin("##SecondViewportUI", nullptr, flags)) {
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100.0f);
		if (ImGui::Button("##ViewportArrow", ImVec2(20.0f, 20.0f)))
			ImGui::OpenPopup("##ViewportArrowMenu");
		ImGui::PopStyleVar();

		if (ImGui::BeginPopup("##ViewportArrowMenu")) {
			static int camSpeed = 20;
			if (ImGui::SliderInt("##CamSpeed", &camSpeed, 20, 300)) {
				camSpeed = (camSpeed / 20) * 20;
				m_scene->editCamera.setCameraSpeed(camSpeed);
			}

			ImGui::EndPopup();
		}

		ImGui::End();
	}
}

void Hyko::EViewport::init()
{
	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Viewport", nullptr, winFlags);
	m_fbo->setFramebufferWidth(ImGui::GetWindowSize().x);
	m_fbo->setFramebufferHeight(ImGui::GetWindowSize().y);
	ECamera::Resize(m_fbo->getFramebufferWidth(), m_fbo->getFramebufferHeight());

	ImGui::Image((void*)m_fbo->getFBOTexture(), { (float)m_fbo->getFramebufferWidth(), (float)m_fbo->getFramebufferHeight() }, {0, 1}, {1, 0});

	secondUILayer();

	ImGui::End();
	ImGui::PopStyleVar();
}
