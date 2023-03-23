#include "Scene.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/System/FileSystem/LogFiles.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Entity.h"

#include <iostream>
#include <algorithm>

Hyko::Time Hyko::Scene::m_tm;

void Hyko::Scene::setIndividualEntityName(Entity checkedEntity)
{
    static int copyCounter = 0;

    auto& tag = checkedEntity.getComponent<TagComponent>().Tag;

    int iteratorBegin = -1;

    m_reg.each([&](auto entityID) {
        Entity entity{ entityID };
        if ((uint32_t)checkedEntity != (uint32_t)entity) {
            if (tag == entity.getComponent<TagComponent>().Tag) {
                if (tag.find('(') != std::string::npos && tag.find(')') != std::string::npos)
                    checkedEntity.getComponent<TagComponent>().Tag.erase(tag.find('(') - 1, tag.find(')'));
                checkedEntity.getComponent<TagComponent>().Tag += " (" + std::to_string(copyCounter++) + ")";
            }
        }
        });
}

Hyko::Entity Hyko::Scene::addToScene()
{
    Hyko::LogF::addMsgToLog("A new entity has been added to the scene");
    Entity ent = m_reg.create();

    ent.addComponent<Hyko::TagComponent>().Tag = ("Entity" + std::to_string((uint32_t)ent));;
    ent.addComponent<Hyko::TransformComponent>();

    return ent;
}

Hyko::Entity Hyko::Scene::addToScene(Hyko::Entity copyEntity)
{
    Hyko::LogF::addMsgToLog("A copy entity has been added to the scene");
    return m_reg.create(copyEntity.get());
}

bool Hyko::Scene::deleteEntity(uint32_t entityID)
{
    Hyko::LogF::addMsgToLog("Entity removed (" + entityID + ')');

    if (m_reg.destroy(Hyko::Entity{ entt::entity(entityID) }.get()))
        return true;
    else
        return false;
}

Hyko::Entity Hyko::Scene::copyEntity(Entity from)
{
    Entity copy = m_reg.create();
   
    from.visit([&](const auto component) {
        using comp = std::decay_t<decltype(component)>;
        copy.addComponent<comp>();
        copy.copyComponent<comp>(from, copy);
        });

    setIndividualEntityName(copy);

    return copy;
}

void Hyko::Scene::Update(float dt)
{
    // create group in entt::registry with SpriteComponent, TransformComponent and IDComponent
    // SpriteComponent - for rendering entity
    // TransformComponent - for transformation entity
    // IDComponent - for identification entity in scene
    auto group = m_reg.group<SpriteComponent>(entt::get<TransformComponent>);

    // check if the entity has SpriteComponent for rendering
    for (auto entity : group) {
        auto [transform, sprite] = m_reg.get<TransformComponent, SpriteComponent>(entity);

        if (sprite.type == Hyko::SpriteComponent::Triangle) 
            Renderer::createTriangle(transform.Transform, sprite.Color);
        if (sprite.type == Hyko::SpriteComponent::Rectangle) 
            Renderer::createRectangle(transform.Transform, sprite.Color);
        if (sprite.type == Hyko::SpriteComponent::Circle) 
            Renderer::createCircle(transform.Transform, sprite.Color, m_reg.get<Hyko::SpriteComponent>(entity).circleSegmentCount);
    }

    // render entities
    Renderer::render();
}

int Hyko::Scene::getEntityCount()
{
    return m_reg.view<Hyko::TransformComponent>().size();
}

void Hyko::Scene::setBackgroundColor(float color[3])
{
    backgroundColor.r = color[0];
    backgroundColor.g = color[1];
    backgroundColor.b = color[2];
}

void Hyko::Scene::setBackgroundColor(float r, float g, float b, float a)
{
    backgroundColor.r = r;
    backgroundColor.g = g;
    backgroundColor.b = b;
}

void Hyko::Scene::setBackgroundColor(glm::vec3 color)
{
    backgroundColor = color;
}
