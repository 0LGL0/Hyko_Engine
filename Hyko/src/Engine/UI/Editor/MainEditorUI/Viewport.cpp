#include "Viewport.h"

#include "Engine/Scene/Camera/EditorCamera.h"
#include "Engine/Scene/Entity/Entity.h"

#include "Engine/Events/InputEvents.h"

#include "Engine/Math/Math.h"

#include "Engine/System/Debug/Log.h"

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

void Hyko::EViewport::viewportMenuBar()
{
	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove;

	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100);
	if (ImGui::Button("##ViewportArrow", ImVec2(20.0f, 20.0f))) 
		ImGui::OpenPopup("ViewportArrowMenu");
	ImGui::PopStyleVar();

	ImGui::SetCursorPosX(ImGui::GetWindowContentRegionWidth() - (ImGui::GetItemRectSize().x * 4));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
	ImGui::Separator();
	if (m_gizmoMode == ImGuizmo::WORLD) {
		if (ImGui::Button("L##Local", ImVec2(20.0f, 20.0f)))
			m_gizmoMode = ImGuizmo::LOCAL;
	}
	else {
		if (ImGui::Button("G##Global", ImVec2(20.0f, 20.0f)))
			m_gizmoMode = ImGuizmo::WORLD;
	}
		
	if (ImGui::Button("T##Translate", ImVec2(20.0f, 20.0f)))
		m_gizmoOperation = ImGuizmo::TRANSLATE_X | ImGuizmo::TRANSLATE_Y;
	else if (ImGui::Button("S##Scale", ImVec2(20.0f, 20.0f)))
		m_gizmoOperation = ImGuizmo::SCALE_X | ImGuizmo::SCALE_Y;
	else if (ImGui::Button("R##Rotate", ImVec2(20.0f, 20.0f)))
		m_gizmoOperation = ImGuizmo::ROTATE_Z;
	ImGui::PopStyleVar();
	ImGui::SetCursorPosX(0.0f);

	if (ImGui::BeginPopup("ViewportArrowMenu", flags)) {
		static int camSpeed = 40;
		ImGui::AlignTextToFramePadding();
		ImGui::Text("Camera speed");
		ImGui::SameLine();
		if (ImGui::SliderInt("##CamSpeed", &camSpeed, 20, 300)) {
			camSpeed = (camSpeed / 20) * 20;
			m_scene->editCamera->setCamSpeed(camSpeed);
		}

		ImGui::EndPopup();
	}
}

void Hyko::EViewport::gizmo(const std::set<uint32_t> selectedEntities)
{
	if (!selectedEntities.empty()) {
		auto firstEntity = Entity::toEntity(*selectedEntities.begin());
		auto translateOffset = firstEntity.getComponent<Hyko::TransformComponent>().translate;
		auto scaleOffset = firstEntity.getComponent<Hyko::TransformComponent>().scale;
		auto rotOffset = firstEntity.getComponent<Hyko::TransformComponent>().rotAngle;

		auto projMat = m_scene->editCamera->getProjMat();
		auto viewMat = m_scene->editCamera->getViewMat();
		ImGuizmo::SetDrawlist();

		float windowWidth  = (float)m_fbo->getFramebufferWidth();
		float windowHeight = (float)m_fbo->getFramebufferHeight();

		ImGuizmo::SetRect(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y, windowWidth, windowHeight);

		auto& transform = Entity::toEntity(*selectedEntities.begin()).getComponent<Hyko::TransformComponent>();
		auto transformMat = transform.getTransform();
		ImGuizmo::Manipulate(glm::value_ptr(viewMat), glm::value_ptr(projMat), m_gizmoOperation, m_gizmoMode, glm::value_ptr(transformMat));
		if (ImGuizmo::IsUsing()) {
			glm::vec2 translate;
			glm::vec2 scale;
			float rot;

			Hyko::Math::decomposeTransformMat(transformMat, translate, scale, rot);

			firstEntity.getComponent<Hyko::TransformComponent>().translate = translate;
			firstEntity.getComponent<Hyko::TransformComponent>().scale = scale;
			firstEntity.getComponent<Hyko::TransformComponent>().rotAngle += glm::degrees(rot) - transform.rotAngle;

			if (selectedEntities.size() > 1) {
				translateOffset -= firstEntity.getComponent<Hyko::TransformComponent>().translate;
				scaleOffset -= firstEntity.getComponent<Hyko::TransformComponent>().scale;
				rotOffset -= firstEntity.getComponent<Hyko::TransformComponent>().rotAngle;
			}

			for (auto entity : selectedEntities) {
				if (entity != (uint32_t)firstEntity) {
					auto iterationEntity = Entity::toEntity(entity);

					iterationEntity.getComponent<Hyko::TransformComponent>().translate -= translateOffset;
					iterationEntity.getComponent<Hyko::TransformComponent>().scale -= scaleOffset;
					iterationEntity.getComponent<Hyko::TransformComponent>().rotAngle += (glm::degrees(rot) - transform.rotAngle) - rotOffset;
				}
			}
		}
	}
}

void Hyko::EViewport::init(const std::set<uint32_t> selectedEntities)
{
	const ImGuiWindowFlags winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar;

	ImGuizmo::SetOrthographic(true);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("Viewport", nullptr, winFlags);
	ImGui::PopStyleVar();
	m_fbo->setFramebufferWidth(ImGui::GetWindowSize().x);
	m_fbo->setFramebufferHeight(ImGui::GetWindowSize().y);
	//m_scene->editCamera->resize(m_fbo->getFramebufferWidth(), m_fbo->getFramebufferHeight());

	ImGui::Image((void*)m_fbo->getFBOTexture(), { (float)m_fbo->getFramebufferWidth(), (float)m_fbo->getFramebufferHeight() }, {0, 1}, {1, 0});

	gizmo(selectedEntities);

	if (ImGui::BeginMenuBar()) {
		viewportMenuBar();

		ImGui::EndMenuBar();
	}

	if (!ImGuizmo::IsUsing()) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_W) && !Hyko::Input::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT))
			m_gizmoOperation = ImGuizmo::TRANSLATE_X | ImGuizmo::TRANSLATE_Y;
		else if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_E) && !Hyko::Input::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT))
			m_gizmoOperation = ImGuizmo::ROTATE_Z;
		else if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_R) && !Hyko::Input::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT))
			m_gizmoOperation = ImGuizmo::SCALE_X | ImGuizmo::SCALE_Y;
	}	

	ImGui::End();
}
