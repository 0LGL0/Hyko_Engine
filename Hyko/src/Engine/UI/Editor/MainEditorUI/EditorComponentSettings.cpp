#include "EditorComponentSettings.h"

#include "Engine/UI/UIFunctions.h"

#include "Engine/System/Debug/Log.h"

void Hyko::EComponentSettings::TagComponent(Entity entity, const ImGuiTreeNodeFlags flags)
{
	char entityNameBuf[20];
	strcpy_s(entityNameBuf, entity.getComponent<Hyko::TagComponent>().Tag.c_str());
	const ImGuiInputTextFlags entityNameFlags = ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue;

	if (ImGui::TreeNodeEx(entity.getComponent<Hyko::TagComponent>().compName.c_str(), flags)) {
		if (componentDeleteMenu<Hyko::TagComponent>(entity))
			return;

		if (ImGui::InputText("Entity name", entityNameBuf, sizeof(entityNameBuf), entityNameFlags))
			entity.getComponent<Hyko::TagComponent>().Tag = entityNameBuf;

		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::TransformComponent(Entity entity, const ImGuiTreeNodeFlags flags)
{
	bool isSliderClicked = false;

	HykoComponentsMenuConfig componentsMenuFlags = HykoComponentsMenuConfig_None;

	if (ImGui::TreeNodeEx(entity.getComponent<Hyko::TransformComponent>().compName.c_str(), flags)) {
		if (componentDeleteMenu<Hyko::TransformComponent>(entity))
			return;

		HykoUI::ComponentsMenu<Hyko::TransformComponent>(entity, componentsMenuFlags);

		if (ImGui::DragFloat2("Position", glm::value_ptr(entity.getComponent<Hyko::TransformComponent>().translate), 0.1f, -FLT_MAX, FLT_MAX))
			isSliderClicked = true;
		if (ImGui::DragFloat2("Scale", glm::value_ptr(entity.getComponent<Hyko::TransformComponent>().scale), 0.1f, 0.0f, FLT_MAX))
			isSliderClicked = true;
		if (ImGui::DragFloat("Rotation", &entity.getComponent<Hyko::TransformComponent>().rotAngle, 0.1f, -360.0f, 360.0f))
			isSliderClicked = true;

		if (isSliderClicked) {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().translate, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(entity.getComponent<Hyko::TransformComponent>().rotAngle), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().scale, 0.0f });

			// TMP: this code will be updated in the future
			/*glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(entity.getComponent<Hyko::TransformComponent>().rotAngle), { 0.0f, 0.0f, 1.0f })
				* glm::translate(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().translate, 0.0f })
				* glm::scale(glm::mat4(1.0f), { entity.getComponent<Hyko::TransformComponent>().scale, 0.0f });*/

			entity.getComponent<Hyko::TransformComponent>().Transform = transform;
		}
		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::SpriteComponent(Entity entity, const ImGuiTreeNodeFlags flags)
{
	auto &style = ImGui::GetStyle();

	if (ImGui::TreeNodeEx(entity.getComponent<Hyko::SpriteComponent>().compName.c_str(), flags)) {
		if (componentDeleteMenu<Hyko::SpriteComponent>(entity))
			return;

		if (ImGui::BeginCombo("Primitive type", Hyko::getSpriteTypeName(entity.getComponent<Hyko::SpriteComponent>().type).c_str())) {
			if (ImGui::Selectable("Triangle"))
				entity.getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Triangle;
			if (ImGui::Selectable("Rectangle"))
				entity.getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Rectangle;
			if (ImGui::Selectable("Circle"))
				entity.getComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Circle;

			ImGui::EndCombo();
		}

		if (entity.getComponent<Hyko::SpriteComponent>().type == Hyko::SpriteComponent::Circle) 
			ImGui::SliderInt("Circle segment count", &entity.getComponent<Hyko::SpriteComponent>().circleSegmentCount, 0, 50);

		ImGui::ColorEdit4("Mesh color", glm::value_ptr(entity.getComponent<Hyko::SpriteComponent>().Color));

		ImGui::TreePop();
	}
}

void Hyko::EComponentSettings::ComponentsFilter(Entity entity)
{
	static const ImVec2 buttonSize = {250.0f, 20.0f};
	const ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

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
			if (ImGui::MenuItem("Tag component"))
				if(!entity.hasAllComponent<Hyko::TagComponent>())
					entity.addComponent<Hyko::TagComponent>();
		}

		if (filter.PassFilter("Transform component")) {
			if (ImGui::MenuItem("Transform component"))
				if (!entity.hasAllComponent<Hyko::TransformComponent>())
					entity.addComponent<Hyko::TransformComponent>();
		}

		if (filter.PassFilter("Sprite component")) {
			if (ImGui::MenuItem("Sprite component"))
				if (!entity.hasAllComponent<Hyko::SpriteComponent>())
					entity.addComponent<Hyko::SpriteComponent>();
		}
		ImGui::EndPopup();
	}
}

void Hyko::EComponentSettings::init(Entity entity)
{
	ImGui::Begin("Component settings");
		const ImGuiTreeNodeFlags categoryTreeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding
			| ImGuiTreeNodeFlags_SpanAvailWidth;

		if(entity.hasAllComponent<Hyko::TagComponent>())
			TagComponent(entity, categoryTreeFlags);
		if(entity.hasAllComponent<Hyko::TransformComponent>())
			TransformComponent(entity, categoryTreeFlags);
		if (entity.hasAllComponent<Hyko::SpriteComponent>())
			SpriteComponent(entity, categoryTreeFlags);

		ComponentsFilter(entity);

		ImGui::End();
}
