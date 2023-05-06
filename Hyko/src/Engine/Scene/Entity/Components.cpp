#include "Components.h"

#include "Engine/Scene/Entity/Entity.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Math/Math.h"

int Hyko::IDComponent::IDCount = 0;

std::string Hyko::getSpriteTypeName(SpriteComponent::Type type)
{
	switch (type) {
	case Hyko::SpriteComponent::Triangle: 
		return "Triangle";
		break;
	case Hyko::SpriteComponent::Rectangle:
		return "Rectangle";
		break;
	case Hyko::SpriteComponent::Circle:
		return "Circle";
		break;
	case Hyko::SpriteComponent::Entity:
		return "Entity";
		break;
	default:
		HK_ERROR("This type does not exist");
	}
}

void Hyko::GroupComponent::addEntityToGroup(const uint32_t entityID)
{
	auto& oldGroupComp = Entity::toEntity(entityID).getComponent<GroupComponent>();
	if (oldGroupComp.isChild) {
		auto& oldParentGroup = Entity::toEntity(oldGroupComp.parent).getComponent<GroupComponent>();
		const auto it = std::find(oldParentGroup.group.begin(), oldParentGroup.group.end(), entityID);
		if(!oldParentGroup.isChild)
			oldGroupComp.isChild = false;
		if (it != oldParentGroup.group.end())
			oldParentGroup.group.erase(it);
	}
	if (std::find(group.begin(), group.end(), entityID) == group.end())
		group.push_back(entityID);
	if (group.size() > 1)
		std::sort(group.begin(), group.end());
}

void Hyko::GroupComponent::moveToMainBranch(const uint32_t entityID)
{
	auto& parentGroup = Entity::toEntity(parent).getComponent<Hyko::GroupComponent>();
	const auto it = std::find(parentGroup.group.begin(), parentGroup.group.end(), entityID);
	isChild = false;
	if (it != parentGroup.group.end()) {
		parentGroup.group.erase(it);
		if (parentGroup.group.empty())
			parentGroup.isParent = false;
	}
	parent = -1;
}

void Hyko::TransformComponent::setTransform(glm::mat4 transform)
{
	Hyko::Math::decomposeTransformMat(transform, translate, scale, rotAngle);
}