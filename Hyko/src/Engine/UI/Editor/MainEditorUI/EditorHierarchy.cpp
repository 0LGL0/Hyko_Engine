#include "EditorHierarchy.h"
#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Components.h"
#include "Engine/UI/UIFunctions.h"

void Hyko::EHierarchy::createNewTree(Entity entity)
{
	auto tag = entity.getComponent<Hyko::TagComponent>().Tag;

	ImGuiTreeNodeFlags treeFlags = (entity == m_selectedEntity) ? ImGuiTreeNodeFlags_Selected : 0 | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeFlags, tag.c_str());

	if (ImGui::IsItemClicked())
		m_selectedEntity = entity;
	if (opened)
		ImGui::TreePop();

	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::Selectable("Delete entity")) {
			m_scene->deleteEntity(entity);

			if (m_selectedEntity == entity)
				m_selectedEntity = {};
		}

		ImGui::EndPopup();
	}
}

void Hyko::EHierarchy::init()
{
	const ImGuiPopupFlags popupFlags = ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight;

	ImGui::Begin("Hierarchy");
		m_scene->m_reg.each([&](auto entityID) {
			Entity entity{ entityID };
			createNewTree(entity);
			});

		if (ImGui::BeginPopupContextWindow(0, popupFlags)) {
			if (ImGui::Selectable("Create entity")) {
				Entity entity = m_scene->addToScene();

				entity.addComponent<Hyko::TagComponent>().Tag = ("Entity" + std::to_string(entity));
				entity.addComponent<Hyko::TransformComponent>().Transform = glm::mat4(1.0f);

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		ImGui::End();
}
