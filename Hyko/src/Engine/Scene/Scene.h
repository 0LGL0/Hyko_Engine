#pragma once

#include "Engine/Core/Macro.h"
#include "Engine/Scene/Entity/Components.h"

#include "Engine/System/Time.h"

#include "Camera/EditorCamera.h"

// std
#include <vector>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entt.hpp"

namespace Hyko {
	class Scene {
	public:
		//ECamera editCamera;
		std::shared_ptr<Camera> editCamera = std::make_shared<Camera>();
	private:
		glm::vec3 backgroundColor{1.0f, 1.0f, 1.0f};

		entt::registry m_reg;

		friend class EHierarchy;
		friend class Entity;
		friend class EComponentSettings;
		friend class EMainPanel;
	private:
		static Time m_tm;
	private:
		void setIndividualEntityName(Entity checkedEntity);
	public:
		std::set<uint32_t> m_selectedEntities;
	public:
		Hyko::Entity addToScene();
		Hyko::Entity addToScene(Hyko::Entity copyEntity);

		bool deleteEntity(uint32_t entityID);

		Hyko::Entity copyEntity(const Entity from);

		void Update(float dt);

	public: // getters
		int getEntityCount();

		float* getBackgroundColor_Arr() { return glm::value_ptr(backgroundColor); }

		glm::vec3 getBackgroundColor_Vec() { return backgroundColor; }

		entt::registry &Reg() { return m_reg; };

		static Time& getTime() { return m_tm; }

		Scene& get() { return *this; }

		const bool hasInSelectedEntities(const uint32_t entity) const; // Is the transferred entity contained in the selected
	public: // setters
		void setBackgroundColor(float color[3]);
		void setBackgroundColor(float r, float g, float b, float a);
		void setBackgroundColor(glm::vec3 color);
	};
}