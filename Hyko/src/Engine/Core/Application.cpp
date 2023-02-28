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

void App::Init()
{
	Window window{ "Hyko", 1280, 720, 4, 6 };

	/*******************************Get GPU and OpenGL information****************************/

	Hyko::Tools::printGPUAndGLInformations(true);

	/*****************************************************************************************/

	fbo->init();

	eUILayer.createUILayer(window.getNativeWindow());
	Hyko::Entity::setScene(m_scene);

	//Hyko::LogF::addAssertationMsgToLog("UI has been created");

	m_scene->editCamera.setData(Hyko::PerspectiveData{ 45.0f, (float)Window::getWindowWidth(Window::getNativeWindow()) / (float)Window::getWindowHeight(Window::getNativeWindow()), 0.1f, 100.0f });
	/*m_scene->editCamera.setData(Hyko::OrthographicData{ -((float)Window::getWindowWidth(Window::getNativeWindow()) / (float)Window::getWindowHeight(Window::getNativeWindow())),
		(float)Window::getWindowWidth(Window::getNativeWindow()) / (float)Window::getWindowHeight(Window::getNativeWindow()),
		-((float)Window::getWindowWidth(Window::getNativeWindow()) / (float)Window::getWindowHeight(Window::getNativeWindow())),
		(float)Window::getWindowWidth(Window::getNativeWindow()) / (float)Window::getWindowHeight(Window::getNativeWindow()) });*/

	m_scene->editCamera.initProjection();
	projection = m_scene->editCamera.getProjectionMat();
	view = m_scene->editCamera.getViewMat();

	shaderProgram = c_shader->createShaderProgram("Hyko//res//shaders//VBasicShader.glsl", "Hyko//res//shaders//FBasicShader.glsl");

	/*auto tr = m_scene->addToScene();
	m_scene->Reg().emplace<Hyko::TransformComponent>(tr);
	m_scene->Reg().emplace<Hyko::SpriteComponent>(tr);

	m_scene->Reg().get<Hyko::SpriteComponent>(tr).type = Hyko::SpriteComponent::Triangle;*/

	Hyko::Entity ent = m_scene->addToScene();
	ent.addComponent<Hyko::TransformComponent>();
	ent.addComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Rectangle;
	ent.addComponent<Hyko::TagComponent>().Tag = "Rectangle";

	Hyko::Entity ent2 = m_scene->addToScene();
	auto transform = glm::translate(glm::mat4(1.0f), { 0.0f, 20.0f, 0.0f })
		* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f });

	ent2.addComponent<Hyko::TransformComponent>().Transform = transform;
	ent2.addComponent<Hyko::SpriteComponent>().type = Hyko::SpriteComponent::Triangle;
	ent2.addComponent<Hyko::TagComponent>().Tag = "Triangle";

	/*auto entity2 = m_scene->addToScene();
	m_scene->Reg().emplace<Hyko::TransformComponent>(entity2);
	m_scene->Reg().emplace<Hyko::CircleSpriteComponent>(entity2);*/

	//auto entity = m_scene->addToScene();
	//m_scene->Reg().emplace<Hyko::TransformComponent>(entity);
	//m_scene->Reg().emplace<Hyko::CircleSpriteComponent>(entity);

	//glm::mat4 trans = glm::translate(glm::mat4(1.0f), { 0.0f, 20.0f, 0.0f })
	//	* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
	//	* glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f });

	//m_scene->Reg().get<Hyko::TransformComponent>(entity).Transform = trans;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity).Color = { 0.2f, 0.6f, 1.0f, 1.0f };
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity).segmentsCount = 10;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity).radius = 1.0f;

	////m_scene->Reg().get<Hyko::TagComponent>(entity).Tag = "Circle 1";

	//auto entity2 = m_scene->addToScene();
	//m_scene->Reg().emplace<Hyko::TransformComponent>(entity2);
	//m_scene->Reg().emplace<Hyko::CircleSpriteComponent>(entity2);

	//glm::mat4 trans2 = glm::translate(glm::mat4(1.0f), { 30.0f, -20.0f, 0.0f })
	//	* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
	//	* glm::scale(glm::mat4(1.0f), { 3.0f, 3.0f, 1.0f });

	//m_scene->Reg().get<Hyko::TransformComponent>(entity2).Transform = trans2;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity2).Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity2).segmentsCount = 20;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity2).radius = 1.0f;

	////m_scene->Reg().get<Hyko::TagComponent>(entity2).Tag = "Circle 2";

	///*auto entity3 = m_scene->addToScene();
	//m_scene->Reg().emplace<Hyko::TransformComponent>(entity3);
	//m_scene->Reg().emplace<Hyko::CircleSpriteComponent>(entity3);

	//glm::mat4 trans3 = glm::translate(glm::mat4(1.0f), { -50.0f, 20.0f, 0.0f })
	//	* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
	//	* glm::scale(glm::mat4(1.0f), { 3.0f, 3.0f, 1.0f });

	//m_scene->Reg().get<Hyko::TransformComponent>(entity3).Transform = trans3;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity3).Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity3).segmentsCount = 5;
	//m_scene->Reg().get<Hyko::CircleSpriteComponent>(entity3).radius = 5.0f;*/

	////m_scene->Reg().get<Hyko::SpriteComponent>(entity2).type = Hyko::SpriteComponent::Triangle;

	///*glm::mat4 trans = glm::translate(glm::mat4(1.0f), { 10.0f, 10.0f, 0.0f })
	//	* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
	//	* glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f });

	//m_scene->Reg().get<Hyko::TransformComponent>(entity2).Transform = trans;*/

	////auto entity2 = m_scene->addToScene(HK_TRIANGLE, {10.0f, 20.0f}, {20.0f, 20.0f}, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f});
	////m_scene->Reg().emplace<Hyko::TransformComponent>(entity2);
	////m_scene->Reg().emplace<Hyko::SpriteComponent>(entity2);

	////auto entity3 = m_scene->addToScene(HK_TRIANGLE, { -30.0f, 20.0f }, { 50.0f, 40.0f }, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f });
	////m_scene->Reg().emplace<Hyko::TransformComponent>(entity3);
	////m_scene->Reg().emplace<Hyko::SpriteComponent>(entity3);

	///*auto entt1 = m_scene->addToScene(HK_RECTANGLE, { 0.0f, 0.0f }, { 10.0f, 10.0f }, 0.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
	//m_scene->Reg().emplace<Hyko::TransformComponent>(entt1);
	//m_scene->Reg().emplace<Hyko::SpriteComponent>(entt1);*/

	//auto entt2 = m_scene->addToScene();
	//m_scene->Reg().emplace<Hyko::TransformComponent>(entt2);
	//m_scene->Reg().emplace<Hyko::SpriteComponent>(entt2);

	//m_scene->Reg().get<Hyko::SpriteComponent>(entt2).type = Hyko::SpriteComponent::Rectangle;

	//glm::mat4 trans5 = glm::translate(glm::mat4(1.0f), { -30.0f, 10.0f, 0.0f })
	//	* glm::rotate(glm::mat4(1.0f), 0.0f, { 0.0f, 0.0f, 1.0f })
	//	* glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 1.0f });

	//m_scene->Reg().get<Hyko::TransformComponent>(entt2).Transform = trans5;
	//m_scene->Reg().get<Hyko::TagComponent>(entt2).Tag = "Rectangle 1";

	/*auto entt3 = m_scene->addToScene(HK_RECTANGLE, {50.0f,60.0f}, {10.0f, 20.0f}, 0.0f, {0.0f, 0.0f, 1.0f, 1.0f});
	m_scene->Reg().emplace<Hyko::TransformComponent>(entt3);
	m_scene->Reg().emplace<Hyko::SpriteComponent>(entt3);*/

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.getNativeWindow())) {
		float time = (float)glfwGetTime();
		Hyko::Time ts = time - m_LastFrameTime;
		m_LastFrameTime = time;

		glfwPollEvents();

		fbo->bind();
		eUILayer.newFrame();

		glClearColor(m_scene->getBackgroundColor_Vec().r, m_scene->getBackgroundColor_Vec().g, m_scene->getBackgroundColor_Vec().b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// camera input
		m_scene->editCamera.updateInput(ts.getDeltaSeconds(), eUILayer.getCamSpeed());

		view = m_scene->editCamera.updateView();
		projection = m_scene->editCamera.updateProjection();

		c_shader->use();

		// set uniform variables for shaders
		c_shader->setUniformMat4("view", view);
		c_shader->setUniformMat4("projection", projection);

		m_scene->Update(ts.getDeltaSeconds());

		c_shader->unUse();

		fbo->unBind();

		// UI
		eUILayer.OnUpdate(ts);
		eUILayer.Render();

		glfwSwapBuffers(window.getNativeWindow());

		Hyko::Input::resetInput();
	}
}
