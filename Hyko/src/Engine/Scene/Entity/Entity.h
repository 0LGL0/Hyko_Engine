#pragma once

#include "Engine/Scene/Scene.h"
//#include "Engine/System/Debug/Assert.h"
#include "Engine/Utility/Utitlity.h"

#include <entt.hpp>

namespace Hyko {
	class Entity {
	private:
		friend class Scene;

		static std::shared_ptr<Scene> m_scene;
		entt::entity m_entity;
	public:
		Entity() = default;
		Entity(entt::entity entity)
			: m_entity(entity) {};

		static void setScene(const std::shared_ptr<Scene> scene);

		template<typename T, typename... Args>
		T& addComponent(Args&&... args) {
			return m_scene->m_reg.emplace<T>(m_entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent() {
			return m_scene->m_reg.get<T>(m_entity);
		}

		template<typename T>
		void deleteComponent() {
			m_scene->m_reg.erase<T>(m_entity);
		}

		template<typename T>
		bool hasAllComponent() {
			return m_scene->m_reg.all_of<T>(m_entity);
		}

		template<typename T>
		bool hasAnyComponent() {
			return m_scene->m_reg.any_of<T>(m_entity);
		}

		template<typename ...Ignore, typename Func>
		void visit(Func func) {
			if (!HKUtility::has_type_v<Hyko::TagComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::TagComponent>())
					func(this->getComponent<Hyko::TagComponent>());
			if (!HKUtility::has_type_v<Hyko::TransformComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::TransformComponent>())
					func(this->getComponent<Hyko::TransformComponent>());
			if (!HKUtility::has_type_v<Hyko::SpriteComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::SpriteComponent>())
					func(this->getComponent<Hyko::SpriteComponent>());
			if (!HKUtility::has_type_v<Hyko::IDComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::IDComponent>())
					func(this->getComponent<Hyko::IDComponent>());

			// I haven't tested this new code with ignored components, so I can't vouch for it
		}

		template<typename T>
		static void copyComponent(Hyko::Entity& from, Hyko::Entity* to) {
			if(from.hasAllComponent<T>() && to->hasAllComponent<T>())
				from.getComponent<T>().clone(to->getComponent<T>());
		}

		// return entt entity from my "Entity" class
		entt::entity get() { return m_entity; }

		// converting an entity id into an entity
		static Entity toEntity(const uint32_t id) { return Entity{ entt::entity(id) }; }

		bool operator==(Entity& second) const {
			return (m_scene == second.m_scene && m_entity == second.m_entity);
		}
		bool operator!=(Entity& second) const {
			return !(*this == second);
		}
		operator uint32_t() const {
			return (uint32_t)m_entity;
		}
	};
}