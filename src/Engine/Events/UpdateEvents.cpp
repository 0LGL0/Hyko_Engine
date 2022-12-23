#include <glad/glad.h>
#include "../shader.h"
#include "UpdateEvents.h"
#include "../Engine/Scene/Scene.h"
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Window winClass;
Shader c_shader;
extern ImGuiWin GuiWindow;
extern Hyko::Entity entity;
extern Hyko::Scene scene;

void Hyko::EUpdates::EventStart()
{
	window = winClass.getMainGLFWWindow();

	projection = EProj.createOrthoProjection(-100.0f, 100.0f, -100.0f, 100.0f);

	shaderProgram = c_shader.createShaderProgram("res//vertexShader.glsl", "res//fragmentShader.glsl");
}

void Hyko::EUpdates::EventUpdate(Hyko::Time ts)
{
	FPS = Hyko::getFPS(ts.getDeltaMilliseconds());

	view = EProj.createViewMatrix();

	glClearColor(GuiWindow.getSkyBoxColor().r, GuiWindow.getSkyBoxColor().g, GuiWindow.getSkyBoxColor().b, GuiWindow.getSkyBoxColor().a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GuiWindow.createImGuiNewFrame();

	if (GuiWindow.vsync) glfwSwapInterval(1);
	else glfwSwapInterval(0);

	if (GuiWindow.meshRenderLineOnly) Hyko::edgeRenderingLineOnly(true);
	else Hyko::edgeRenderingLineOnly(false);

	////Input//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////Editor camera control//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (Hyko::isMouseButtonPressed(Hyko::Mouse::HK_MOUSE_BUTTON_RIGHT)) {
		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_W))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x, EProj.getEditorCameraPosition().y - 100.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_S))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x, EProj.getEditorCameraPosition().y + 100.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_A))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x + 100.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().y, EProj.getEditorCameraPosition().z);

		if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_D))
			EProj.setEditorCameraPosition(EProj.getEditorCameraPosition().x - 100.0f * ts.getDeltaSeconds(), EProj.getEditorCameraPosition().y, EProj.getEditorCameraPosition().z);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < scene.sceneTriangles.size(); i++) {
		entity.setPosition(i, HK_TRIANGLE, scene.sceneTriangles[i].m_position);
		entity.setScale(i, HK_TRIANGLE, scene.sceneTriangles[i].m_scale);
		entity.setRot(i, HK_TRIANGLE, glm::radians(scene.sceneTriangles[i].m_rotation));
		entity.setColor(i, HK_TRIANGLE, scene.sceneTriangles[i].m_color);
	}

	///////////////////////////////////////////////////////////////////

	c_shader.use();

	////uniform variables in shaders////////////////////////////////////////////////////////////

	c_shader.setUniformMat4("view", view);
	c_shader.setUniformMat4("projection", projection);

	////////////////////////////////////////////////////////////////////////////////////////////

	//if (MainEditoreUI.mashIsCreated(HK_TRIANGLE)) {
		entity.render(HK_TRIANGLE);
		entity.EndDraw();
	//}

	c_shader.unUse();

	////ImGui. Hyko GUI windows///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GuiWindow.ImGui_MainWindowDraw();
	MainEditoreUI.createEditorUI();

	if (GuiWindow.DebugWindowShow)																						   GuiWindow.ImGui_DebugWindowDraw(FPS, ts.getDeltaMilliseconds());
	if (GuiWindow.DisplaySettingsShow)																					   GuiWindow.ImGui_DisplaySettingsWindowDraw();
	if (GuiWindow.SceneSettingsShow)																					   GuiWindow.ImGui_SceneSettingsWindowDraw();
	//if (GuiWindow.ComponentSettings_TreeShow)																			   GuiWindow.ImGui_HykoPrimitiveMeshesEdit();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
