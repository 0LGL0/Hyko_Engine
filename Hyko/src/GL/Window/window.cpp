#include "window.h"

#include "Engine/System/Time.h"
#include "Engine/Events/InputEvents.h"

#include "Engine/System/FileSystem/LogFiles.h"
#include "Engine/System/Debug/Log.h"

GLFWwindow* Window::m_window;

void Window::setupVariebles(int width, int height, std::string title, const int GLMajorVersion, const int GLMinorVersion)
{
	m_WindowData.Width = width;
	m_WindowData.Height = height;
	m_WindowData.Title = title;
	m_WindowData.GLMajorVersion = GLMajorVersion;
	m_WindowData.GLMinorVersion = GLMinorVersion;
}

void Window::setupHints(const int GLMajorVersion, const int GLMinorVersion)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajorVersion); // set opengl major version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinorVersion); // set opengl minor version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set opengl core profile
}

void Window::setupGLAD()
{
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // installing glad (modern opengl functions)
}

Window::Window(std::string title, int width, int height, const int GLMajorVersion, const int GLMinorVersion) {
	setupVariebles(width, height, title, GLMajorVersion, GLMinorVersion);

	glfwInit(); // init glfw

	setupHints(GLMajorVersion, GLMinorVersion);

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); // creating window
	glfwMakeContextCurrent(m_window);

	// Lambdas
	// Lambda for glfw window resize callback
	/*glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});*/

	/*glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		HK_WARN("{0}, {1}", width, height);
		glViewport(0, 0, width, height);
		});*/

	// Lambda for glfw scroll callback
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		Hyko::Input::setMouseXOffset((float)xOffset);
	Hyko::Input::setMouseYOffset((float)yOffset);
		});

	// Lambda for glfw cursor position callback
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
		Hyko::Input::setMouseXPos(xPos);
	Hyko::Input::setMouseYPos(yPos);
		});

	setupGLAD();

	Hyko::LogF::init();
	if (m_window) Hyko::LogF::addMsgToLog("Window has been created (" + std::to_string(getWindowWidth()) + std::to_string(getWindowHeight()));
	else Hyko::LogF::addErrorMsgToLog("The window was not created");
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) Hyko::LogF::addMsgToLog("GLAD has been initialized");
	else Hyko::LogF::addErrorMsgToLog("GLAD was not initialized");
}

Window::~Window()
{
	glfwTerminate();
	glfwDestroyWindow(m_window);

	Hyko::LogF::addMsgToLog("The window is destroyed");
}

int Window::getWindowWidth(GLFWwindow* window)
{
	int w = 0;

	glfwGetWindowSize(window, &w, nullptr);

	return w;
}

int Window::getWindowHeight(GLFWwindow* window)
{
	int h = 0;

	glfwGetWindowSize(window, nullptr, &h);

	return h;
}

void Window::setVSync(bool state)
{
	glfwSwapInterval(state);
}

void Window::setWindowWidth(int width)
{
	m_WindowData.Width = width;
}

void Window::setWindowHeight(int height)
{
	m_WindowData.Height = height;
}

void Window::setWindowWidth(Window &window, int width)
{
	window.setWindowWidth(width);
}

void Window::setWindowHeight(Window &window, int height)
{
	window.setWindowHeight(height);
}

void Window::setRenderEdges(const bool value)
{
	switch (value)
	{
	case true:
		glPolygonMode(GL_FRONT, GL_LINE);
		break;
	case false:
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	}
}