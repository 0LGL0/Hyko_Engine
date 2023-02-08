#pragma once

#include "Engine/Core/Macro.h"
#include "Engine/Meshes/Components.h"

#include "Engine/System/FileSystem/shader.h"

#include "Camera/EditorCamera.h"

// std
#include <vector>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "entt.hpp"

namespace Hyko {
	struct Scene {
	public:
		ECamera editCamera;
	private:
		glm::vec3 backgroundColor{1.0f, 1.0f, 1.0f};

		entt::registry m_reg;
	public:
		std::vector<Hyko::Triangle> sceneTriangles;
		size_t trianglesCount = 0;
		size_t rectangleCount = 0;

		template<typename T>
		T getSceneComponent(int indx, int8_t type) {
			if (type == HK_TRIANGLE) {
				for (int i = 0; i < sceneTriangles.size(); i++) {
					if (sceneTriangles[i].indx == indx) return sceneTriangles[i];
				}
			}
		}

		entt::entity addToScene();

		void Update(float dt);

	public: // getters
		int getComponentCount(int8_t type);

		float* getBackgroundColor_Arr() { return glm::value_ptr(backgroundColor); }

		glm::vec3 getBackgroundColor_Vec() { return backgroundColor; }

		entt::registry &Reg() { return m_reg; };
	public: // setters
		void setBackgroundColor(float color[3]);
		void setBackgroundColor(float r, float g, float b, float a);
		void setBackgroundColor(glm::vec3 color);
	};
}