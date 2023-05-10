#include "EditorHierarchy.h"

#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Components.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Buffers/Windows/Clipboard.h"


void Hyko::EHierarchy::createNewTree(Entity entity)
{
	auto &tag = entity.getComponent<Hyko::TagComponent>().Tag;
	auto& groupComp = entity.getComponent<Hyko::GroupComponent>();
	static std::set<uint32_t> draggedEntities;
	bool opened = false;
	ImGuiTreeNodeFlags treeFlags = ImGuiTreeNodeFlags_OpenOnArrow;

	if (groupComp.group.empty())
		ImGui::Selectable(tag.c_str(), (std::binary_search(m_scene->m_selectedEntities.begin(), m_scene->m_selectedEntities.end(), (uint32_t)entity)) ? true : false, ImGuiSelectableFlags_SpanAllColumns);
	else {
		treeFlags |= (std::binary_search(m_scene->m_selectedEntities.begin(), m_scene->m_selectedEntities.end(), (uint32_t)entity)) ? ImGuiTreeNodeFlags_Selected : 0;
		opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, treeFlags, tag.c_str());
	}
	
	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_AcceptNoDrawDefaultRect)) {
		ImGui::SetDragDropPayload("Entities", &m_scene->m_selectedEntities, sizeof(std::set<uint32_t>));
		draggedEntities = m_scene->m_selectedEntities;
		ImGui::Text(tag.c_str());
		ImGui::EndDragDropSource();
	}

	/*
	* when we drag the object(s) to an empty place in the window, 
	* the object(s) are moved to the main branch, that is, they are removed from all groups
	*/
	if (ImGui::IsDragDropActive() && ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem) && !ImGui::IsAnyItemHovered()) {
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
			for (const uint32_t draggedID : draggedEntities) {
				if (Entity::toEntity(draggedID).getComponent<Hyko::GroupComponent>().isChild)
					Entity::toEntity(draggedID).getComponent<Hyko::GroupComponent>().moveToMainBranch(Entity::toEntity(draggedID));
			}
		}
	}

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entities")) {
			HK_ASSERT(payload->DataSize == sizeof(std::set<uint32_t>));

			auto &payloadData = *(const std::set<uint32_t>*)payload->Data;
			if (payloadData.find((uint32_t)entity) == payloadData.end()) {
				for (const uint32_t draggedID : payloadData) {
					if (groupComp.addEntityToGroup(draggedID, (uint32_t)entity)) {
						auto& draggedGroup = Entity::toEntity(draggedID).getComponent<Hyko::GroupComponent>();
						groupComp.isParent = true;
						draggedGroup.parent = (uint32_t)entity;
						draggedGroup.isChild = true;
					}
				}
			}
		} 

		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemClicked()) {
		if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_LEFT_CONTROL) || Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_RIGHT_CONTROL))
			m_scene->m_selectedEntities.insert((uint32_t)entity);
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
		if (ImGui::MenuItem("Delete entity", "Del"))
			deleteEntity();
		else {
			if (groupComp.isChild) {
				if (ImGui::MenuItem("Move to main branch", "Ctrl + RMB"))
					groupComp.moveToMainBranch((uint32_t)entity);
			}
		}

		if (ImGui::MenuItem("Create child entity")) {
			Entity newEntity = m_scene->addToScene();
			auto &newEntityGroup = newEntity.getComponent<Hyko::GroupComponent>();
			groupComp.addEntityToGroup((uint32_t)newEntity, (uint32_t)entity);
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

void Hyko::EHierarchy::deleteEntity()
{
	for (const auto id : m_scene->m_selectedEntities) {
		auto& iterationGroupComp = Entity::toEntity(id).getComponent<Hyko::GroupComponent>();
		if (iterationGroupComp.isChild) {
			auto& iterationParentGroupComp = Entity::toEntity(iterationGroupComp.parent).getComponent<Hyko::GroupComponent>();
			iterationParentGroupComp.group.erase(std::find(iterationParentGroupComp.group.begin(), iterationParentGroupComp.group.end(), id));
		}
		if (iterationGroupComp.isParent) {
			for (const auto childID : iterationGroupComp.group)
				Entity::toEntity(childID).getComponent<Hyko::GroupComponent>().isChild = false;
			iterationGroupComp.group.clear();
		}

		m_scene->deleteEntity(id);
	}
	m_scene->m_selectedEntities.clear();
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

	if (Hyko::Input::isKeyPressed(Hyko::Key::HK_KEYBOARD_DELETE))
		deleteEntity();

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
