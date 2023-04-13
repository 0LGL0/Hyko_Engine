#include "EditorComponentSettings.h"

#include "Engine/System/Debug/Log.h"
#include "Engine/Buffers/Windows/Clipboard.h"

void Hyko::EComponentSettings::TagComponent(Entity entity, const ImGuiTreeNodeFlags flags)
{
	char entityNameBuf[20];
	strcpy_s(entityNameBuf, entity.getComponent<Hyko::TagComponent>().Tag.c_str());
	auto entityID = std::to_string((uint32_t)entity);
	const ImGuiInputTextFlags entityNameFlags = ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue;

	if (ImGui::TreeNodeEx(entity.getComponent<Hyko::TagComponent>().compName.c_str(), flags)) {
		// Entity ID
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
		if (ImGui::Button(entityID.c_str(), ImVec2(ImGui::GetFrameHeight(), ImGui::GetFrameHeight()))) {
			HK_INFO("ID coped");
			Clipboard::inClipboard(entityID);
		}
		ImGui::SameLine();

		// Entity name
		if (ImGui::InputText("Entity name", entityNameBuf, sizeof(entityNameBuf), entityNameFlags)) {
			entity.getComponent<Hyko::TagComponent>().Tag = entityNameBuf;
			m_scene->setIndividualEntityName(entity);
		}
		ImGui::PopStyleVar();

		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::TransformComponent(const ImGuiTreeNodeFlags flags, std::set<uint32_t> entities)
{
	bool isSliderClicked = false;
	auto firstEntity = Entity::toEntity(*entities.begin());
	auto translateOffset = firstEntity.getComponent<Hyko::TransformComponent>().translate;
	auto scaleOffset = firstEntity.getComponent<Hyko::TransformComponent>().scale;
	auto rotOffset	= firstEntity.getComponent<Hyko::TransformComponent>().rotAngle;

	if (ImGui::TreeNodeEx(firstEntity.getComponent<Hyko::TransformComponent>().compName.c_str(), flags)) {
		if (ImGui::DragFloat2("Position", glm::value_ptr(firstEntity.getComponent<Hyko::TransformComponent>().translate), 0.1f, -FLT_MAX, FLT_MAX))
			isSliderClicked = true;
		if (ImGui::DragFloat2("Scale", glm::value_ptr(firstEntity.getComponent<Hyko::TransformComponent>().scale), 0.1f, 0.0f, FLT_MAX))
			isSliderClicked = true;
		if (ImGui::DragFloat("Rotation", &firstEntity.getComponent<Hyko::TransformComponent>().rotAngle, 0.1f, -360.0f, 360.0f))
			isSliderClicked = true;

		if (entities.size() > 1) {
			translateOffset -= firstEntity.getComponent<Hyko::TransformComponent>().translate;
			scaleOffset -= firstEntity.getComponent<Hyko::TransformComponent>().scale;
			rotOffset -= firstEntity.getComponent<Hyko::TransformComponent>().rotAngle;
		}

		if (isSliderClicked) {
			for (auto i : entities) {
				auto iterationEntity = Entity::toEntity(i);

				if (entities.size() > 1) {
					if (iterationEntity != firstEntity) {
						iterationEntity.getComponent<Hyko::TransformComponent>().translate = glm::vec2(iterationEntity.getComponent<Hyko::TransformComponent>().translate.x - translateOffset.x,
							iterationEntity.getComponent<Hyko::TransformComponent>().translate.y - translateOffset.y);
						iterationEntity.getComponent<Hyko::TransformComponent>().scale = glm::vec2(iterationEntity.getComponent<Hyko::TransformComponent>().scale.x - scaleOffset.x,
							iterationEntity.getComponent<Hyko::TransformComponent>().scale.y - scaleOffset.y);
						iterationEntity.getComponent<Hyko::TransformComponent>().rotAngle = iterationEntity.getComponent<Hyko::TransformComponent>().rotAngle - rotOffset;
					}
				}

				/*glm::mat4 transform = glm::translate(glm::mat4(1.0f), { iterationEntity.getComponent<Hyko::TransformComponent>().translate, 0.0f })
					* glm::rotate(glm::mat4(1.0f), glm::radians(iterationEntity.getComponent<Hyko::TransformComponent>().rotAngle), { 0.0f, 0.0f, 1.0f })
					* glm::scale(glm::mat4(1.0f), { iterationEntity.getComponent<Hyko::TransformComponent>().scale, 0.0f });*/

				// TMP: this code will be updated in the future
				/*glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(entity.getComponent<Hyko::TransformComponent>().rotAngle), { 0.0f, 0.0f, 1.0f })
					* glm::translate(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().translate, 0.0f })
					* glm::scale(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().scale, 0.0f });*/

				//iterationEntity.getComponent<Hyko::TransformComponent>().Transform = transform;
			}
		}
		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::SpriteComponent(const ImGuiTreeNodeFlags flags, std::set<uint32_t> entities)
{
	auto &style = ImGui::GetStyle();

	auto firstEntity = Entity::toEntity(*entities.begin());

	if (ImGui::TreeNodeEx(firstEntity.getComponent<Hyko::SpriteComponent>().compName.c_str(), flags)) {
		if (componentDeleteMenu<Hyko::SpriteComponent>(firstEntity)) {
			for (auto i : entities) {
				if (Entity::toEntity(i) != firstEntity) {
					if (Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).deleteComponent<Hyko::SpriteComponent>();
				}
			}
			return;
		}

		if (ImGui::BeginCombo("Primitive type", Hyko::getSpriteTypeName(firstEntity.getComponent<Hyko::SpriteComponent>().type).c_str())) {
			if (ImGui::Selectable("Triangle")) {
				for (auto i : entities) {
					if(Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Triangle;
				}
			}
			if (ImGui::Selectable("Rectangle")) {
				for (auto i : entities) {
					if (Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Rectangle;
				}
			}
			if (ImGui::Selectable("Circle")) {
				for (auto i : entities) {
					if (Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Circle;
				}
			}

			ImGui::EndCombo();
		}

		if (firstEntity.getComponent<Hyko::SpriteComponent>().type == Hyko::SpriteComponent::Circle) {
			ImGui::SliderInt("Circle segment count", &firstEntity.getComponent<Hyko::SpriteComponent>().circleSegmentCount, 5, 50);
			for (auto i : entities) {
				if (Entity::toEntity(i) != firstEntity) {
					if (Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).getComponent<Hyko::SpriteComponent>().circleSegmentCount = firstEntity.getComponent<Hyko::SpriteComponent>().circleSegmentCount;
				}
			}
		}

		if (ImGui::ColorEdit4("Mesh color", glm::value_ptr(firstEntity.getComponent<Hyko::SpriteComponent>().Color))) {
			if (entities.size() > 1) {
				for (auto i : entities) {
					if (Entity::toEntity(i) != firstEntity) {
						if (Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
							Entity::toEntity(i).getComponent<Hyko::SpriteComponent>().Color = firstEntity.getComponent<Hyko::SpriteComponent>().Color;
					}
				}
			}
		}
		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::ComponentsFilter(std::set<uint32_t> entities)
{
	static const ImVec2 buttonSize = {250.0f, 20.0f};
	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	auto firstEntity = Entity::toEntity(*entities.begin());

	ImGui::Separator();
	ImGui::Indent((ImGui::GetWindowWidth() - buttonSize.x) / 2.0f);

	if (ImGui::ButtonEx("Add component", buttonSize)) {
		ImGui::OpenPopup("Component_menu");

		ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x - 30.0f / 2.0f, ImGui::GetItemRectMax().y));
	}

	ImGui::Indent();
	
	// filtering components
	if (ImGui::BeginPopup("Component_menu", flags)) {
		ImGuiTextFilter filter;
		filter.Draw("##filter", buttonSize.x + 30.0f);

		if (filter.PassFilter("Tag component")) {
			if (ImGui::MenuItem("Tag component")) {
				for (auto i : entities) {
					if (!Entity::toEntity(i).hasAllComponent<Hyko::TagComponent>())
						Entity::toEntity(i).addComponent<Hyko::TagComponent>();
				}
			}
		}

		if (filter.PassFilter("Transform component")) {
			if (ImGui::MenuItem("Transform component")) {
				for (auto i : entities) {
					if (!Entity::toEntity(i).hasAllComponent<Hyko::TransformComponent>())
						Entity::toEntity(i).addComponent<Hyko::TransformComponent>();
				}
			}
		}

		if (filter.PassFilter("Sprite component")) {
			if (ImGui::MenuItem("Sprite component")) {
				for (auto i : entities) {
					if (!Entity::toEntity(i).hasAllComponent<Hyko::SpriteComponent>())
						Entity::toEntity(i).addComponent<Hyko::SpriteComponent>();
				}
			}
		}
		ImGui::EndPopup();
	}
}

void Hyko::EComponentSettings::init(std::set<uint32_t> entities)
{
	ImGui::Begin("Component settings");
	if (!entities.empty()) {
		const ImGuiTreeNodeFlags categoryTreeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding
			| ImGuiTreeNodeFlags_SpanAvailWidth;

		auto firstEntity = Entity::toEntity(*entities.begin());

		if (firstEntity.hasAllComponent<Hyko::TagComponent>())
			TagComponent(firstEntity, categoryTreeFlags);
		if (firstEntity.hasAllComponent<Hyko::TransformComponent>())
			TransformComponent(categoryTreeFlags, entities);
		if (firstEntity.hasAllComponent<Hyko::SpriteComponent>())
			SpriteComponent(categoryTreeFlags, entities);

		ComponentsFilter(entities);
	}

		ImGui::End();
}
