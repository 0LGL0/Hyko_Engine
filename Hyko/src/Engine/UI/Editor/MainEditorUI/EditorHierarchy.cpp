#include "EditorHierarchy.h"
#include "Engine/Core/Macro.h"

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
		if (!m_scene->sceneTriangles.empty()) {
			for (int i = 0; i < m_scene->sceneTriangles.size(); i++) {
				if(m_scene->sceneTriangles[i].type == HK_TRIANGLE)
					createNewTree(HK_TRIANGLE, m_scene->sceneTriangles[i].indx);
			}
		}

		ImGui::End();
	}
}
