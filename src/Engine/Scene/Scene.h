#pragma once

#include "../Core/Hyko.h"
#include <vector>

namespace Hyko {
	struct Scene {
		std::vector<Hyko::Triangle> sceneTriangles;

		template<typename T>
		T getSceneComponent(int indx, int8_t type) {
			if (type == HK_TRIANGLE) {
				for (int i = 0; i < sceneTriangles.size(); i++) {
					if (sceneTriangles[i].indx == indx) return sceneTriangles[i];
				}
			}
		}

		// getters
		int getComponentCount(int8_t type);
	};
}