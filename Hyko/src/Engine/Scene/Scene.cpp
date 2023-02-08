#include "Scene.h"

#include "Engine/Renderer/Renderer.h"

#include <iostream>

entt::entity Hyko::Scene::addToScene()
{
    return m_reg.create();
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

        if(sprite.type == Hyko::SpriteComponent::Triangle)
            Renderer::createTriangle(transform.Transform, sprite.Color);
        
        if (sprite.type == Hyko::SpriteComponent::Rectangle)
            Renderer::createRectangle(transform.Transform, sprite.Color);
    }
    for (auto entity : circleGroup) {
        auto [transform, sprite] = m_reg.get<TransformComponent, CircleSpriteComponent>(entity);

        Renderer::createCircle(transform.Transform, sprite.Color, sprite.segmentsCount, sprite.radius);
    }

    // render entities
    Renderer::render();
}

int Hyko::Scene::getComponentCount(int8_t type)
{
    if (type == HK_TRIANGLE)
        return sceneTriangles.size();

    return 0;
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
