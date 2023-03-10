#include "Scene.h"

#include "Engine/Renderer/Renderer.h"

#include "Engine/System/FileSystem/LogFiles.h"
#include "Engine/System/Debug/Log.h"
#include "Engine/Scene/Entity/Entity.h"

#include <iostream>

Hyko::Time Hyko::Scene::m_tm;

entt::entity Hyko::Scene::addToScene()
{
    Hyko::LogF::addMsgToLog("A new entity has been added to the scene");
    auto ent = m_reg.create();

    return ent;
}

bool Hyko::Scene::deleteEntity(uint32_t entityID)
{
    if (m_reg.destroy(Hyko::Entity{ entt::entity(entityID) }.get()))
        return true;
    else
        return false;
}

void Hyko::Scene::Update(float dt)
{
    // create group in entt::registry with SpriteComponent, TransformComponent and IDComponent
    // SpriteComponent - for rendering entity
    // TransformComponent - for transformation entity
    // IDComponent - for identification entity in scene
    auto group = m_reg.group<SpriteComponent>(entt::get<TransformComponent>);
    auto circleGroup = m_reg.group<CircleSpriteComponent>(entt::get<TransformComponent>);

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
