#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/System/Debug/Assert.h"
#include "Engine/Utility/Utitlity.h"

#include <entt.hpp>
#include <vector>
#include <typeinfo>

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
			if (hasAllComponent<T>())
				HK_WARN("Entity({0}) already has {1}", (uint32_t)m_entity, typeid(T).name());
			else
				return m_scene->m_reg.emplace<T>(m_entity, std::forward<Args>(args)...);
		}

		template<typename T>
		T& getComponent() {
			if (hasAllComponent<T>())
				return m_scene->m_reg.get<T>(m_entity);
			else {
				HK_WARN("The entity({0}) does not have a {1} to get this component", (uint32_t)m_entity, typeid(T).name());
				abort();
			}
		}

		template<typename T>
		void deleteComponent() {
			if (hasAllComponent<T>())
				m_scene->m_reg.erase<T>(m_entity);
			else
				HK_WARN("The entity({0}) does not have a {1} to delete", (uint32_t)m_entity, typeid(T).name());
		}

		template<typename T>
		bool hasAllComponent() const {
			return m_scene->m_reg.all_of<T>(m_entity);
		}

		template<typename T>
		bool hasAnyComponent() const {
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
			if (!HKUtility::has_type_v<Hyko::RelativeTransformComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::RelativeTransformComponent>())
					func(this->getComponent<Hyko::RelativeTransformComponent>());
			if (!HKUtility::has_type_v<Hyko::SpriteComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::SpriteComponent>())
					func(this->getComponent<Hyko::SpriteComponent>());
			if (!HKUtility::has_type_v<Hyko::IDComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::IDComponent>())
					func(this->getComponent<Hyko::IDComponent>());
			if (!HKUtility::has_type_v<Hyko::GroupComponent, Ignore...>)
				if (this->hasAllComponent<Hyko::GroupComponent>())
					func(this->getComponent<Hyko::GroupComponent>());

			// I haven't tested this new code with ignored components, so I can't vouch for it
		}

		template<typename T>
		static void copyComponent(Hyko::Entity& from, Hyko::Entity* to) {
			const bool comparison = (from.m_entity == to->m_entity && from.m_scene == to->m_scene);
			const bool has = (from.hasAllComponent<T>() && to->hasAllComponent<T>());
			if (has && !comparison)
				from.getComponent<T>().clone(to->getComponent<T>());
			else if (comparison)
				HK_WARN("Why copy a {0} from one entity({1}) to the same one({2})?", typeid(T).name(), (uint32_t)from, (uint32_t)to);
			else if(!has){
				HK_WARN("One or two entities({0} and {1}) do not have a {2} to copy", (uint32_t)from, (uint32_t)to, typeid(T).name());
				abort();
			}
		}

		const bool alive() const { return m_scene->Reg().valid(m_entity); }

		// return entt entity from my "Entity" class
		entt::entity get() { return m_entity; }

		// converting an entity id into an entity
		static Entity toEntity(const uint32_t id) { return Entity{ entt::entity(id) }; }

		bool operator==(Entity& second) const { return (m_scene == second.m_scene && m_entity == second.m_entity); }
		bool operator!=(Entity& second) const { return !(*this == second); }
		operator uint32_t() const { return (uint32_t)m_entity; }
	};
}