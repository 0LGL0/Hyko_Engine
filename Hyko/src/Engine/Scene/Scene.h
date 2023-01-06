#pragma once

#include "Engine/Core/Macro.h"
#include "Engine/Meshes/Components.h"

// std
#include <vector>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hyko {
	struct Scene {
	private:
		glm::vec3 backgroundColor{1.0f, 1.0f, 1.0f};
	public:
		std::vector<Hyko::Triangle> sceneTriangles;

		template<typename T>
		T getSceneComponent(int indx, int8_t type) {
			if (type == HK_TRIANGLE) {
				for (int i = 0; i < sceneTriangles.size(); i++) {
					if (sceneTriangles[i].indx == indx) return sceneTriangles[i];
				}
			}
		}

	public: // getters
		int getComponentCount(int8_t type);

		float* getBackgroundColor_Arr() { return glm::value_ptr(backgroundColor); }

		glm::vec3 getBackgroundColor_Vec() { return backgroundColor; }
	public: // setters
		void setBackgroundColor(float color[3]);
		void setBackgroundColor(float r, float g, float b, float a);
		void setBackgroundColor(glm::vec3 color);
	};
}