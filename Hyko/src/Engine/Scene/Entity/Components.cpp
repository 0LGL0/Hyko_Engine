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

bool Hyko::GroupComponent::addEntityToGroup(const uint32_t newEntityID, const uint32_t srcEntityID)
{
	auto& oldGroupComp = Entity::toEntity(newEntityID).getComponent<GroupComponent>();
	auto& srcGroupComp = Entity::toEntity(srcEntityID).getComponent<Hyko::GroupComponent>();
	if (oldGroupComp.isChild) {
		auto& oldParentGroup = Entity::toEntity(oldGroupComp.parent).getComponent<GroupComponent>();
		const auto it = std::find(oldParentGroup.group.begin(), oldParentGroup.group.end(), newEntityID);
		if(!oldParentGroup.isChild)
			oldGroupComp.isChild = false;
		if (it != oldParentGroup.group.end())
			oldParentGroup.group.erase(it);
	}

	/*
	* This check is necessary in order to prevent a bug in which it was possible to move the parent object to its child.
	* Here we go through all the parent entities of the "srcEntityID" entity and if one of these entities is "newEntityID"
	* we return false, thereby not adding the "newEntityID" entity to the group
	*/
	if (srcGroupComp.isChild && oldGroupComp.isParent) {
		uint32_t tmpParent = srcGroupComp.parent;
		while (tmpParent != (uint32_t)-1) {
			if (tmpParent == newEntityID) return false;
			else tmpParent = Entity::toEntity(tmpParent).getComponent<Hyko::GroupComponent>().parent;
		}
	}
	if (std::find(group.begin(), group.end(), newEntityID) == group.end())
		group.push_back(newEntityID);
	if (group.size() > 1)
		std::sort(group.begin(), group.end());

	return true;
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