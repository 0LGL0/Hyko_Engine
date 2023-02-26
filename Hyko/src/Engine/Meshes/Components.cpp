#include "Components.h"
#include "Engine/System/Debug/Log.h"

int Hyko::Triangle::count = 0;
int Hyko::IDComponent::IDCount = 0;

std::string Hyko::getSpriteTypeName(SpriteComponent::Type type)
{
	switch (type) {
	case 0: 
		return "Triangle";
		break;
	case 1:
		return "Rectangle";
		break;
	case 2:
		return "Circle";
		break;
	default:
		HK_ERROR("This type does not exist");
	}
}
