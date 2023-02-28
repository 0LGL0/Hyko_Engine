#include "EngineUILayer.h"

#include "Engine/Core/Macro.h"

#include "GL/Window/window.h"

#include "Engine/System/FileSystem/LogFiles.h"

// imgui
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

	Hyko::LogF::addMsgToLog("Engine UI layer destroyed");
} 

void Hyko::EUILayer::createUILayer(GLFWwindow *window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // I'm giving up on this because it has a very big impact on performance.
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	/*ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}*/  // Viewport
	
	ImGui::StyleColorsDark();

	if (ImGui_ImplGlfw_InitForOpenGL(window, true)
		&& ImGui_ImplOpenGL3_Init("#version 460")) {
		Hyko::LogF::addMsgToLog("Engine UI layer created");
	}
	else Hyko::LogF::addErrorMsgToLog("Engine UI layer not created");
}

void Hyko::EUILayer::OnUpdate(Time dt)
{
	float time = (float)glfwGetTime();
	Hyko::Time ts = time - m_LastFrameTime;
	m_LastFrameTime = time;

	mainPan.init();

	/*eToolbar.createEToolbar(Hyko::getFPS(ts.getDeltaMilliseconds()), ts.getDeltaMilliseconds());
	eHierarchy.createHierarchy();
	eCompSettings.createComponentSettings();*/


	if (eToolbar.meshLineMode) Window::setRenderEdges(true);
	if (!eToolbar.meshLineMode) Window::setRenderEdges(false);

	if (eToolbar.VSync)			Window::setVSync(true);
	if (!eToolbar.VSync)		Window::setVSync(false);

	m_scene->setBackgroundColor(eToolbar.backgroundColor);

	m_scene->editCamera.swapProjection(eToolbar.projectionTypeIndx == 0 ? Hyko::projType::Perspective : Hyko::projType::Orthographic);

	ImGui::ShowDemoWindow();
}

void Hyko::EUILayer::renderEnities()
{
	/*for (int i = 0; i < m_scene->sceneTriangles.size(); i++) {
		m_entity->setPosition(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_position);
		m_entity->setScale(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_scale);
		m_entity->setRot(i, HK_TRIANGLE, glm::radians(m_scene->sceneTriangles[i].m_rotation));
		m_entity->setColor(i, HK_TRIANGLE, m_scene->sceneTriangles[i].m_color);
	}

	if (eToolbar.meshIsCreting) {
		m_entity->render(HK_TRIANGLE);
		m_entity->EndDraw();
	}*/
}

void Hyko::EUILayer::Render()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = { (float)Window::getWindowWidth(Window::getNativeWindow()), (float)Window::getWindowHeight(Window::getNativeWindow()) };

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	/*if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(current_context);
	}*/ // Viewport
}