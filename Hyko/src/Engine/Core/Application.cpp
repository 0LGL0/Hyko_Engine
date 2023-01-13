#include "Application.h"

#include "Engine/Scene/Scene.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/Debug/Debug.h"

//GL
#include <glad/glad.h>
#include <glfw3.h>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>

void App::Init()
{
	Window window{ "Hyko", 1280, 720, 3, 3 };

	eUILayer.createUILayer(window.getNativeWindow());

	eCamera->setData(Hyko::PerspectiveData{ 90.0f, 1280.0f / 720.0f, 0.1f, 100.0f });
	eCamera->setData(Hyko::OrthographicData{ -100.0f, 100.0f, -100.0f, 100.0f });

	eCamera->initProjection();
	projection = eCamera->getProjectionMat();
	view = eCamera->getViewMat();

	shaderProgram = c_shader.createShaderProgram("Hyko//res//vertexShader.glsl", "Hyko//res//fragmentShader.glsl");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.getNativeWindow())) {
		float time = (float)glfwGetTime();
		Hyko::Time ts = time - m_LastFrameTime;
		m_LastFrameTime = time;

		glfwPollEvents();

		glClearColor(m_scene->getBackgroundColor_Vec().r, m_scene->getBackgroundColor_Vec().g, m_scene->getBackgroundColor_Vec().b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		eUILayer.newFrame();

		// input
		eCamera->updateInput(ts.getDeltaSeconds(), eUILayer.getCamSpeed());
		view = eCamera->updateView();
		projection = eCamera->updateProjection();

		c_shader.use();

		// set uniform variables for shaders
		c_shader.setUniformMat4("view", view);
		c_shader.setUniformMat4("projection", projection);

		eUILayer.renderEnities();

		c_shader.unUse();

		// UI
		eUILayer.OnUpdate(ts);
		eUILayer.Render();

		glfwSwapBuffers(window.getNativeWindow());

		Hyko::Input::resetInput();
	}
}
