#include "EngineUILayer.h"

#include "Engine/Debug/Debug.h"
#include "Engine/Core/Macro.h"

#include "GL/Window/window.h"

// imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void Hyko::EUILayer::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

Hyko::EUILayer::~EUILayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Hyko::EUILayer::createUILayer(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	//newFrame(); // create new frame for imgui
}

void Hyko::EUILayer::OnUpdate(Time dt)
{
	float time = (float)glfwGetTime();
	Hyko::Time ts = time - m_LastFrameTime;
	m_LastFrameTime = time;

	eToolbar.createEToolbar(Hyko::getFPS(ts.getDeltaMilliseconds()), ts.getDeltaMilliseconds());
	eHierarchy.createHierarchy();
	eCompSettings.createComponentSettings();


	if (eToolbar.meshLineMode) edgeRenderingLineOnly(true);
	if (!eToolbar.meshLineMode) edgeRenderingLineOnly(false);

	if (eToolbar.VSync)			Window::setVSync(true);
	if (!eToolbar.VSync)		Window::setVSync(false);

	m_scene->setBackgroundColor(eToolbar.backgroundColor);
}

void Hyko::EUILayer::renderEnities()
{
	for (int i = 0; i < m_scene->sceneTriangles.size(); i++) {
		m_entity->setPosition(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_position);
		m_entity->setScale(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_scale);
		m_entity->setRot(i, HK_TRIANGLE, glm::radians(m_scene->sceneTriangles[i].m_rotation));
		m_entity->setColor(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_color);
	}

	if (eToolbar.meshIsCreting) {
		m_entity->render(HK_TRIANGLE);
		m_entity->EndDraw();
	}
}

void Hyko::EUILayer::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
