#include "EditorHierarchy.h"

#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Components.h"
#include "Engine/UI/UIFunctions.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Buffers/Windows/Clipboard.h"

void Hyko::EHierarchy::createNewTree(Entity entity)
{
	auto &tag = entity.getComponent<Hyko::TagComponent>().Tag;

	ImGuiTreeNodeFlags treeFlags = (entity == m_selectedEntity) ? ImGuiTreeNodeFlags_Selected : 0 | ImGuiTreeNodeFlags_OpenOnArrow;
	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeFlags, tag.c_str());

	if (tag.size() >= 20) // 20 is the maximum number of symbols in the entity name buffer
		entity.getComponent<Hyko::TagComponent>().Tag.pop_back();

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

void Hyko::EHierarchy::copingEntity()
{
	static bool entityCoped = false;

	if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_C))) {
		Clipboard::inClipboard(std::to_string((uint32_t)m_selectedEntity) + "hce");
		entityCoped = true;
	}


	if (entityCoped) {
		if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
			&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_V))) {
			std::string clipboardData = Clipboard::outClipboard();
			const size_t dsprBeginIter = clipboardData.find('h'); // The iterator of the beginning of the entity ID descriptor
			if (clipboardData	[dsprBeginIter]		== 'h'
				&& clipboardData[dsprBeginIter + 1] == 'c'
				&& clipboardData[dsprBeginIter + 2] == 'e') {
				const auto& id = clipboardData.erase(dsprBeginIter, 3);
				if (!id.empty())
					m_scene->copyEntity(Entity::toEntity(std::stoi(id)));
				else HK_ERROR("Entity ID does not exist in clipboard. ID: ({0})", id);
			}
			entityCoped = false;
		}
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

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		copingEntity();

		ImGui::End();
}
