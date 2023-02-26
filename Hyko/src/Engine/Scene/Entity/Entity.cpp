#include "Entity.h"

std::shared_ptr<Hyko::Scene> Hyko::Entity::m_scene;

void Hyko::Entity::setScene(std::shared_ptr<Scene> scene)
{
	m_scene = scene;
}
