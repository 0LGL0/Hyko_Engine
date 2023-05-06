#include "Entity.h"

std::shared_ptr<Hyko::Scene> Hyko::Entity::m_scene;

void Hyko::Entity::setScene(std::shared_ptr<Scene> scene)
{
	m_scene = scene;
}

//void Hyko::Entity::addEntityToGroup(uint32_t entityID)
//{
//	std::set<uint32_t>::iterator it;
//	m_group.push_back(entityID);
//	if ((it = m_scene->m_selectedEntities.find(entityID)) != m_scene->m_selectedEntities.end())
//		m_scene->m_selectedEntities.erase(it);
//	if (m_group.size() > 1)
//		std::sort(m_group.begin(), m_group.end());
//}