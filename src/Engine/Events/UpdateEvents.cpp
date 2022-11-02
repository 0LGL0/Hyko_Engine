#include <glad/glad.h>
#include "UpdateEvents.h"
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Window winClass;
extern ImGuiWin GuiWindow;

void Hyko::EUpdates::EventStart()
{
	window = winClass.getMainGLFWWindow();

	projection = EProj.createOrthoProjection(-1.0f, 1.0f, -1.0f, 1.0f);

	triangle.createTriangle();
}

void Hyko::EUpdates::EventUpdate(Hyko::Time ts)
{
	FPS = dbg.getFPS(ts.getDeltaSeconds());

	view = EProj.createViewMatrix(); 

	glClearColor(GuiWindow.skyBoxColor[0], GuiWindow.skyBoxColor[1], GuiWindow.skyBoxColor[2], GuiWindow.skyBoxColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);

	GuiWindow.createImGuiNewFrame();

	if (GuiWindow.vsync) glfwSwapInterval(1);
	else glfwSwapInterval(0);

	if (GuiWindow.meshRenderLineOnly) dbg.edgeRenderingLineOnly(true);
	else dbg.edgeRenderingLineOnly(false);

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
			GuiWindow.createTriangle			 = false;
			GuiWindow.itemSelected				 = false;
			GuiWindow.ComponentSettings_TreeShow = false;
		}
	}

	///////////////////////////////////////////////////////////////////

	////uniform variables in shaders////////////////////////////////////////////////////////////

	viewUniformLocation = glGetUniformLocation(triangle.getShaderProgram(), "view");
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	projUniformLocation = glGetUniformLocation(triangle.getShaderProgram(), "projection");
	glUniformMatrix4fv(projUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	////////////////////////////////////////////////////////////////////////////////////////////

	triangle.meshRender();

	////ImGui. Hyko GUI windows///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GuiWindow.ImGui_MainWindowDraw();
	GuiWindow.ImGui_SceneComponentsWindowDraw();
	GuiWindow.ImGui_HykoPrimitiveMeshes();

	if (GuiWindow.DebugWindowShow)																						   GuiWindow.ImGui_DebugWindowDraw(FPS, ts.getDeltaMilliseconds());
	if (GuiWindow.DisplaySettingsShow)																					   GuiWindow.ImGui_DisplaySettingsWindowDraw();
	if (GuiWindow.createTriangle /*|| GuiWindow.createRectangle || GuiWindow.createCircle || GuiWindow.createStaticMesh*/) GuiWindow.ImGui_HykoPrimitiveMeshesEdit();
	if (GuiWindow.SceneSettingsShow)																					   GuiWindow.ImGui_SceneSettingsWindowDraw();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
