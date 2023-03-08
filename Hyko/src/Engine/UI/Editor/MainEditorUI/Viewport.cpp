#include "Viewport.h"
#include "Engine/Scene/Camera/EditorCamera.h"

#include <imgui.h>

void Hyko::EViewport::init()
{
	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Viewport", nullptr, winFlags);
	m_fbo->setFramebufferWidth(ImGui::GetWindowSize().x);
	m_fbo->setFramebufferHeight(ImGui::GetWindowSize().y);
	ECamera::Resize(m_fbo->getFramebufferWidth(), m_fbo->getFramebufferHeight());

	ImGui::Image((void*)m_fbo->getFBOTexture(), { (float)m_fbo->getFramebufferWidth(), (float)m_fbo->getFramebufferHeight() }, {0, 1}, {1, 0});

	ImGui::End();
	ImGui::PopStyleVar();
}
