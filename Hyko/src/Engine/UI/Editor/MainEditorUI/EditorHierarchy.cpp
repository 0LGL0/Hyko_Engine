#include "EditorHierarchy.h"

#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Components.h"
#include "Engine/UI/UIFunctions.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Buffers/Windows/Clipboard.h"

#include <algorithm>

void Hyko::EHierarchy::createNewTree(Entity entity)
{
	auto &tag = entity.getComponent<Hyko::TagComponent>().Tag;
	ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow;
	if(m_selectedEntities.size() == 1)
		treeFlags |= (*m_selectedEntities.begin() == (uint32_t)entity) ? ImGuiTreeNodeFlags_Selected : 0;
	else
		treeFlags |= (std::binary_search(m_selectedEntities.begin(), m_selectedEntities.end(), (uint32_t)entity)) ? ImGuiTreeNodeFlags_Selected : 0;

	bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeFlags, tag.c_str());

	if (ImGui::IsItemClicked()) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
			m_selectedEntities.insert((uint32_t)entity);
			
		else {
			if (m_selectedEntities.size() <= 1) {
				m_selectedEntities.clear();
				m_selectedEntities.insert(m_selectedEntities.begin(), (uint32_t)entity);
			}
			else {
				m_selectedEntities.clear();
				m_selectedEntities.insert((uint32_t)entity);
			}
		}
	}

	if (tag.size() >= 20) // 20 is the maximum number of symbols in the entity name buffer
		entity.getComponent<Hyko::TagComponent>().Tag.pop_back();

	if (opened)
		ImGui::TreePop();

	if (ImGui::BeginPopupContextItem()) {
		if (ImGui::Selectable("Delete entity")) {
			if(m_selectedEntities.size() == 1)
				m_scene->deleteEntity(entity);
			else {
				for(auto i: m_selectedEntities)
					m_scene->deleteEntity(i);
			}
			m_selectedEntities.clear();
		}

		ImGui::EndPopup();
	}
}

void Hyko::EHierarchy::copingEntity()
{
	static bool entityCoped = false;

	if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_C))) {
		std::string copingEntity;
		for (auto i : m_selectedEntities)
			copingEntity += (std::to_string((uint32_t)i) + "hce");
		Clipboard::inClipboard(copingEntity);
		entityCoped = true;
	}

	if (entityCoped) {
		if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
			&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_V))) {
			std::string clipboardData = Clipboard::outClipboard();
			std::string tmpID;

			for (int i = 0; i < clipboardData.size(); i++) {
				if (clipboardData[i] != 'h' && clipboardData[i] != 'c' && clipboardData[i] != 'e')
					tmpID.push_back(clipboardData[i]);
				else if(clipboardData[i] == 'h'){
						m_scene->copyEntity(Entity::toEntity(std::stoi(tmpID)));
						tmpID = "";
				}
			}
			entityCoped = false;
		}
	}
}

void Hyko::EHierarchy::init()
{
	static const ImGuiPopupFlags popupFlags = ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight;
	size_t treeID = 0;

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

		if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) {
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
				m_selectedEntities.clear();
			}
		}

		ImGui::End();
}
