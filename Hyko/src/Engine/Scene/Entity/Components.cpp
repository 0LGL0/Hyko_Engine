#include "Components.h"
#include "Engine/System/Debug/Log.h"

int Hyko::Triangle::count = 0;
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
