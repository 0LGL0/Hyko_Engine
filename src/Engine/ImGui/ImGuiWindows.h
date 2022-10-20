#pragma once
#include <glfw3.h>
#include <glm/glm.hpp>
#include <string>

class ImGuiWin {
	std::string FPSTitle;
	std::string msTitle;

	std::string componentTreeName;

	int triangleCount = 0;

public:
	////Mesh settings variables//////////////////////////////////

	glm::vec3 triangleNewPos;
	glm::vec3 triangleNewScale = glm::vec3(0.5f, 0.5f, 0.5f);

	float triangleColor[4];

	//////////////////////////////////////////////////////////////

	////Scene variables///////////////////////////////////////////

	float skySphereColor[4]{1.0f, 1.0f, 1.0f, 1.0f};

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

	bool vsync		= false;
	bool createTriangle = false;

	///////////////////////////////////////////


	////ImGui window create/////////////////////////

	void createImGuiWindow(GLFWwindow* glfwWindow);
	void createImGuiNewFrame();

	////////////////////////////////////////////////


	////ImGui. Engine window draw///////////////////

	void ImGui_MainWindowDraw();
	void ImGui_DebugWindowDraw(int fps, double ms);
	void ImGui_DisplaySettingsWindowDraw();
	void ImGui_SceneComponentsWindowDraw();
	void ImGui_SceneSettingsWindowDraw();
	void ImGui_HykoPrimitiveMeshes();
	void ImGui_HykoPrimitiveMeshesEdit();

	////////////////////////////////////////////////


	void ImGuiRender();
	void ImGuiWindowShutDown();
};
