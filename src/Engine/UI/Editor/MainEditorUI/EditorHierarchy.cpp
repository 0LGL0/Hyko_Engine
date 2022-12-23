#include "EditorHierarchy.h"
#include "../Engine/Scene/Scene.h"
#include "../Engine/Core/Hyko.h"

extern Hyko::Scene scene;

void Hyko::EHierarchy::createNewTree(int8_t type, int indx)
{
	std::string nameOfTree;

	if (type == HK_TRIANGLE)
		nameOfTree = "Triangle" + std::to_string(indx);

	if (ImGui::TreeNode(nameOfTree.c_str())) {

		ImGui::TreePop();
	}
}

void Hyko::EHierarchy::createHierarchy()
{
	//ImGuiWindowFlags winFlags = ImGuiWindowFlags_Modal;

	if (ImGui::Begin("Hierarchy")) {
		if (!scene.sceneTriangles.empty()) {
			for (int i = 0; i < scene.sceneTriangles.size(); i++) {
				if(scene.sceneTriangles[i].type == HK_TRIANGLE)
					createNewTree(HK_TRIANGLE, scene.sceneTriangles[i].indx);
			}
		}

		ImGui::End();
	}
}
