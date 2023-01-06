#pragma once

// GL
#include <glad/glad.h>
#include <glfw3.h>

// std
#include <string>

struct WindowData {
	int Width = 0;
	int Height = 0;

	std::string Title;
	
	int GLMajorVersion = 0;
	int GLMinorVersion = 0;
};

enum WindowStates {
	Edit, Play, Stop, Simulate
};

class Window {
private:
	static GLFWwindow* m_window;

	WindowData m_WindowData;
private:
	using callbackF = void(*)(GLFWwindow* win, int width, int height);
private:
	void setupVariebles(int width, int height, std::string title, const int GLMajorVersion, const int GLMinorVersion);
	void setupHints(const int GLMajorVersion, const int GLVersionMinor);
	void setupGLAD();
public:
	Window() = default;
	Window(std::string title, int width, int height, const int GLMajorVersion, const int GLVersionMinor);
	~Window();

public: // getters
	int getWindowWidth() { return m_WindowData.Width; }
	int getWindowHeight() { return m_WindowData.Height; }

	std::string getWindowTitle() { return m_WindowData.Title; }

	int getGLMajorVersion() const { return m_WindowData.GLMajorVersion; }
	int getGLMinorVersion() const { return m_WindowData.GLMinorVersion; }

	static GLFWwindow* getNativeWindow() { return m_window; }
public: // setters
	static void setVSync(bool state);
};