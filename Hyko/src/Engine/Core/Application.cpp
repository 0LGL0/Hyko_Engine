#include "Application.h"

#include "Engine/Scene/Scene.h"
#include "Engine/Events/InputEvents.h"
#include "Engine/System/Tools.h"
#include "Engine/System/FileSystem/LogFiles.h"

// Debug
#include "Engine/System/Debug/Log.h"
#include "Engine/System/Debug/Assert.h"

//GL
#include <glad/glad.h>
#include <glfw3.h>

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>

void App::lastUpdate()
{
	const auto view = m_scene->Reg().view<Hyko::TransformComponent>();
	for (const auto entityID : view) {
		auto& entityTransform = Hyko::Entity{ entityID }.getComponent<Hyko::TransformComponent>();

		entityTransform.lastTranslate = entityTransform.translate;
		entityTransform.lastScale = entityTransform.scale;
		entityTransform.lastRotAngle = entityTransform.rotAngle;
	}
}

void App::Init()
{
	Window window{ "Hyko", 1280, 720, 4, 6 };

	/*******************************Get GPU and OpenGL information****************************/

	Hyko::Tools::printGPUAndGLInformations(true);

	/*****************************************************************************************/

	m_fbo->init();

	eUILayer.createUILayer(window.getNativeWindow());
	Hyko::Entity::setScene(m_scene);

	shaderProgram = c_shader->createShaderProgram("Hyko//res//shaders//VBasicShader.glsl", "Hyko//res//shaders//FBasicShader.glsl");

	Hyko::Entity ent = m_scene->addToScene();
	ent.addComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Rectangle;

	Hyko::Entity ent2 = m_scene->addToScene();
	auto transform = glm::translate(glm::mat4(1.0f), { 0.0f, 20.0f, 0.0f })
		* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f });

	ent2.addComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Triangle;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.getNativeWindow())) {
		float time = (float)glfwGetTime();
		Hyko::Scene::getTime() = time - m_LastFrameTime;
		m_LastFrameTime = time;

		glfwPollEvents();

		m_fbo->bind();
		eUILayer.newFrame();

		glClearColor(m_scene->getBackgroundColor_Vec().r, m_scene->getBackgroundColor_Vec().g, m_scene->getBackgroundColor_Vec().b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// camera input
		m_scene->editCamera->updateInput(Hyko::Scene::getTime().getDeltaSeconds());

		m_scene->editCamera->updateView();
		m_scene->editCamera->updateProjection(m_fbo);

		view = m_scene->editCamera->getViewMat();
		projection = m_scene->editCamera->getProjMat();

		c_shader->use();

		// set uniform variables for shaders
		c_shader->setUniformMat4("view", view);
		c_shader->setUniformMat4("projection", projection);

		m_scene->Update(Hyko::Scene::getTime().getDeltaSeconds());

		c_shader->unUse();

		m_fbo->unBind();

		lastUpdate(); // update previous frame variables

		// UI
		eUILayer.OnUpdate(Hyko::Scene::getTime());
		eUILayer.Render();

		glfwSwapBuffers(window.getNativeWindow());

		Hyko::Input::resetInput();
	}
}
