#include <glad/glad.h>
#include "../shader.h"
#include "UpdateEvents.h"
#include "../GL/VO.h"
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Window winClass;
Shader c_shader;
extern ImGuiWin GuiWindow;
VO vo;

void Hyko::EUpdates::EventStart()
{
	window = winClass.getMainGLFWWindow();

	projection = EProj.createOrthoProjection(-1.0f, 1.0f, -1.0f, 1.0f);

	shaderProgram = c_shader.createShaderProgram("res//vertexShader.glsl", "res//fragmentShader.glsl");

	triangle.createTriangle();
}

void Hyko::EUpdates::EventUpdate(Hyko::Time ts)
{
	FPS = Hyko::getFPS(ts.getDeltaMilliseconds());

	view = EProj.createViewMatrix();

	glClearColor(GuiWindow.getSkyBoxColor().r, GuiWindow.getSkyBoxColor().g, GuiWindow.getSkyBoxColor().b, GuiWindow.getSkyBoxColor().a);
	glClear(GL_COLOR_BUFFER_BIT);

	GuiWindow.createImGuiNewFrame();

	if (GuiWindow.vsync) glfwSwapInterval(1);
	else glfwSwapInterval(0);

	if (GuiWindow.meshRenderLineOnly) Hyko::edgeRenderingLineOnly(true);
	else Hyko::edgeRenderingLineOnly(false);

	////Input//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////Editor camera control//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (Hyko::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT)) {
		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_W))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x, EProj.getEditorCameraPosition().y - 1.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_S))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x, EProj.getEditorCameraPosition().y + 1.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_A))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x + 1.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().y, EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_D))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x - 1.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().y, EProj.getEditorCameraPosition().z);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////Delete mesh////////////////////////////////////////////////////

	if (GuiWindow.itemSelected) {
		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_DELETE)) {
			GuiWindow.createTriangle = false;
			GuiWindow.itemSelected = false;
			GuiWindow.ComponentSettings_TreeShow = false;
		}
	}

	///////////////////////////////////////////////////////////////////

	c_shader.use();

	////uniform variables in shaders////////////////////////////////////////////////////////////

	viewUniformLocation = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	projUniformLocation = glGetUniformLocation(shaderProgram, "projection");
	glUniformMatrix4fv(projUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	////////////////////////////////////////////////////////////////////////////////////////////

	triangle.meshRender(shaderProgram);

	c_shader.unUse();

	////ImGui. Hyko GUI windows///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GuiWindow.ImGui_MainWindowDraw();
	GuiWindow.ImGui_SceneComponentsWindowDraw();
	GuiWindow.ImGui_HykoPrimitiveMeshes();

	if (GuiWindow.DebugWindowShow)																						   GuiWindow.ImGui_DebugWindowDraw(FPS, ts.getDeltaMilliseconds());
	if (GuiWindow.DisplaySettingsShow)																					   GuiWindow.ImGui_DisplaySettingsWindowDraw();
	if (GuiWindow.SceneSettingsShow)																					   GuiWindow.ImGui_SceneSettingsWindowDraw();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
