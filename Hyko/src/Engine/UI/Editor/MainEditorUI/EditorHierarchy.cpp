#include "EditorHierarchy.h"

#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Components.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Buffers/Windows/Clipboard.h"

#include <algorithm>

void Hyko::EHierarchy::createNewTree(Entity entity)
{
	auto &tag = entity.getComponent<Hyko::TagComponent>().Tag;
	auto& groupComp = entity.getComponent<Hyko::GroupComponent>();
	bool opened = false;
	static bool isDragging = false;
	static uint32_t draggedEntity = -1;
	ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow;

	if (groupComp.group.empty())
		ImGui::Selectable(tag.c_str(), (std::binary_search(m_scene->m_selectedEntities.begin(), m_scene->m_selectedEntities.end(), (uint32_t)entity)) ? true : false, ImGuiSelectableFlags_SpanAllColumns);
	else {
		if (m_scene->m_selectedEntities.size() == 1)
			treeFlags |= (*m_scene->m_selectedEntities.begin() == (uint32_t)entity) ? ImGuiTreeNodeFlags_Selected : 0;
		else
			treeFlags |= (std::binary_search(m_scene->m_selectedEntities.begin(), m_scene->m_selectedEntities.end(), (uint32_t)entity)) ? ImGuiTreeNodeFlags_Selected : 0;

		opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeFlags, tag.c_str());
	}
	
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_AcceptNoDrawDefaultRect)) {
		ImGui::SetDragDropPayload("Entity", &entity, sizeof(Entity));
		draggedEntity = (uint32_t)entity;
		ImGui::Text(tag.c_str());
		ImGui::EndDragDropSource();
	}
	else
		isDragging = false;

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
			HK_ASSERT(payload->DataSize == sizeof(Entity));

			auto payloadData = *(const Entity*)payload->Data;
			if ((uint32_t)entity != (uint32_t)payloadData) {
				groupComp.addEntityToGroup((uint32_t)payloadData);
				auto& draggedGroup = Entity::toEntity(draggedEntity).getComponent<Hyko::GroupComponent>();
				groupComp.isParent = true;
				draggedGroup.parent = (uint32_t)entity;
				draggedGroup.isChild = true;

				HK_INFO(groupComp.group.size());
			}
		} 

		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemClicked()) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL)) {
			m_scene->m_selectedEntities.insert((uint32_t)entity);
			if (Entity::toEntity(draggedEntity).getComponent<Hyko::GroupComponent>().isChild)						
				Entity::toEntity(draggedEntity).getComponent<Hyko::GroupComponent>().moveToMainBranch(Entity::toEntity(draggedEntity));		// <-- TODO: Replace with when dragged tree hovering with only window (This is not what I wanted)
		}
		else {
			if (m_scene->m_selectedEntities.size() <= 1) {
				m_scene->m_selectedEntities.clear();
				m_scene->m_selectedEntities.insert(m_scene->m_selectedEntities.begin(), (uint32_t)entity);
			}
			else {
				m_scene->m_selectedEntities.clear();
				m_scene->m_selectedEntities.insert((uint32_t)entity);
			}
		}
	}

	if (tag.size() >= 20) // 20 is the maximum number of symbols in the entity name buffer
		entity.getComponent<Hyko::TagComponent>().Tag.pop_back();

	rightClickItemMenu(entity);

	if (opened) {
		for (const auto& entityID : groupComp.group)
			createNewTree(Entity::toEntity(entityID));

		ImGui::TreePop();
	}
}

void Hyko::EHierarchy::copingEntity()
{
	static bool entityCoped = false;

	if (((Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
		&& Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_C))) {
		std::string copingEntity;
		for (auto i : m_scene->m_selectedEntities)
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

void Hyko::EHierarchy::rightClickItemMenu(Hyko::Entity entity)
{
	if (ImGui::BeginPopupContextItem()) {
		auto& groupComp = entity.getComponent<Hyko::GroupComponent>();
		if (ImGui::MenuItem("Delete entity", "Del")) {
			for (const auto id : m_scene->m_selectedEntities) {
				if (groupComp.isChild) {
					auto &parentGroupComp = Entity::toEntity(groupComp.parent).getComponent<Hyko::GroupComponent>();
					parentGroupComp.group.erase(std::find(parentGroupComp.group.begin(), parentGroupComp.group.end(), id));
				}
				if (groupComp.isParent) {
					for (const auto childID : groupComp.group)
						Entity::toEntity(childID).getComponent<Hyko::GroupComponent>().isChild = false;
					groupComp.group.clear();
				}

				m_scene->deleteEntity(id);
			}
			m_scene->m_selectedEntities.clear();
		}
		else {
			if (groupComp.isChild) {
				if (ImGui::MenuItem("Move to main branch", "Ctrl + RMB"))
					groupComp.moveToMainBranch((uint32_t)entity);
			}
		}

		if (ImGui::MenuItem("Create child entity")) {
			Entity newEntity = m_scene->addToScene();
			auto &newEntityGroup = newEntity.getComponent<Hyko::GroupComponent>();
			groupComp.addEntityToGroup((uint32_t)newEntity);
			newEntityGroup.isChild = true;
			newEntityGroup.parent = (uint32_t)entity;
			groupComp.isParent = true;
		}

		ImGui::EndPopup();
	}
}

void Hyko::EHierarchy::rightClickWindowMenu(const ImGuiPopupFlags popupFlags)
{
	if (ImGui::BeginPopupContextWindow(0, popupFlags)) {
		if (ImGui::MenuItem("Create entity")) {
			Entity entity = m_scene->addToScene();

			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void Hyko::EHierarchy::init()
{
	static const ImGuiPopupFlags popupFlags = ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight;
	size_t treeID = 0;

	ImGui::Begin("Hierarchy");
	m_scene->m_reg.each([&](auto entityID) {
		Entity entity{ entityID };
		if (entity.alive()) {
			if (!entity.getComponent<Hyko::GroupComponent>().isChild)
				createNewTree(entity);
		}
		});

	rightClickWindowMenu(popupFlags);
	copingEntity();

	if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_DELETE)) {
		for (const auto id : m_scene->m_selectedEntities) 
			m_scene->deleteEntity(id);
		m_scene->m_selectedEntities.clear();
	}

	if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
			m_scene->m_selectedEntities.clear();
		}
	}
	else {
		if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			m_scene->editCamera->setPos(Entity::toEntity(*m_scene->m_selectedEntities.begin()).getComponent<Hyko::TransformComponent>().translate);
	}

	ImGui::End();
}
