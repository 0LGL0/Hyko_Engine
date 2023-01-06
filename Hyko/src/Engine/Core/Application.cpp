#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Scene/Scene.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Debug/Debug.h"

#include "Application.h"

void App::Init()
{
	Window window{ "test", 1280, 720, 3, 3 };
	eUILayer.createUILayer(window.getNativeWindow());

	projection = EProj.createOrthoProjection(-100.0f, 100.0f, -100.0f, 100.0f);

	shaderProgram = c_shader.createShaderProgram("Hyko//res//vertexShader.glsl", "Hyko//res//fragmentShader.glsl");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.getNativeWindow())) {
		float time = (float)glfwGetTime();
		Hyko::Time ts = time - m_LastFrameTime;
		m_LastFrameTime = time;

		view = EProj.createViewMatrix();

		glClearColor(m_scene->getBackgroundColor_Vec().r, m_scene->getBackgroundColor_Vec().g, m_scene->getBackgroundColor_Vec().b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		eUILayer.newFrame();

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

			// reset camera position
			if (Hyko::isKeyPressed(Hyko::Key::HK_KEYBORD_LEFT_CONTROL))
				EProj.setEditorCameraPosition(0.0f, 0.0f, 0.0f);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		c_shader.use();

		////uniform variables in shaders////////////////////////////////////////////////////////////

		c_shader.setUniformMat4("view", view);
		c_shader.setUniformMat4("projection", projection);

		////////////////////////////////////////////////////////////////////////////////////////////

		eUILayer.renderEnities();

		c_shader.unUse();

		// UI
		eUILayer.OnUpdate(ts);

		eUILayer.Render();

		glfwSwapBuffers(window.getNativeWindow());
		glfwPollEvents();
	}
}
