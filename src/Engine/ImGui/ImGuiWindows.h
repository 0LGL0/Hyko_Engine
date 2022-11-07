#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <string>

class ImGuiWin {
	std::string FPSTitle;
	std::string dtTitle;

	std::string componentTreeName;

	int triangleCount = 0;

public:
	////Mesh settings variables//////////////////////////////////

	glm::vec3 m_triangleNewPos;
	glm::vec3 m_triangleNewScale = glm::vec3(0.5f, 0.5f, 0.5f);

	//////////////////////////////////////////////////////////////

	////Scene variables///////////////////////////////////////////

	float m_skyBoxColor[4]{1.0f, 1.0f, 1.0f, 1.0f};
	float m_triangleColor[4]{1.0f, 0.0f, 0.0f};

	//////////////////////////////////////////////////////////////

	////Window show bool///////////////////////

	bool DebugWindowShow	 = false;
	bool DisplaySettingsShow = false;
	bool SceneSettingsShow   = false;

	////Trees widgets//////////////////////////

	bool ComponentSettings_TreeShow = false;

	///////////////////////////////////////////

	///////////////////////////////////////////


	////Functions//////////////////////////////

	bool vsync				= false;
	bool createTriangle		= false;
	bool meshRenderLineOnly = false;
	bool itemSelected		= false;

	///////////////////////////////////////////

	////ImGui window create/////////////////////////

	void createImGuiWindow(GLFWwindow* glfwWindow);
	void createImGuiNewFrame();

	////////////////////////////////////////////////


	////ImGui. Engine window draw///////////////////

	void ImGui_MainWindowDraw();
	void ImGui_DebugWindowDraw(int fps, double dt);
	void ImGui_DisplaySettingsWindowDraw();
	void ImGui_SceneComponentsWindowDraw();
	void ImGui_SceneSettingsWindowDraw();
	void ImGui_HykoPrimitiveMeshes();
	void ImGui_HykoPrimitiveMeshesEdit();

	////////////////////////////////////////////////

	////getters///////////////////////////////////////////////////////////////////////////////////////////

	glm::vec4 getSkyBoxColor() { return glm::vec4(m_skyBoxColor[0], m_skyBoxColor[1], m_skyBoxColor[2], m_skyBoxColor[3]); };

	//////////////////////////////////////////////////////////////////////////////////////////////////////

	/////setters/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void setMeshPosition(glm::vec3 pos) { m_triangleNewPos = pos; };
	void setMeshScale(glm::vec3 scale) { m_triangleNewScale = scale; };

	void setMeshDiffuseColor(glm::vec4 diffColor) { m_triangleColor[0] = diffColor.r; m_triangleColor[1] = diffColor.g; m_triangleColor[2] = diffColor.b; m_triangleColor[3] = diffColor.a; };
	void setMeshDiffuseColor(float* diffColor) { m_triangleColor[0] = diffColor[0]; m_triangleColor[1] = diffColor[1]; m_triangleColor[2] = diffColor[2]; m_triangleColor[3] = diffColor[3]; };

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	void ImGuiRender();
	void ImGuiWindowShutDown();
};
