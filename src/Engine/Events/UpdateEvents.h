#pragma once

#include "../Engine/Projection/EditorProjection.h"
#include "../Engine/ImGui/ImGuiWindows.h"
#include "../Engine/Meshes/Triangle.h"
#include "../Engine/Debug/Debug.h"
#include "../Engine/Core/Hyko.h"
#include "../../window.h"
#include <glm/glm.hpp>

namespace Hyko {
	class EUpdates {
	private:
		EProjection EProj;
	private:
		Triangle triangle;
	private:
		glm::mat4 projection;
		glm::mat4 view;
	private:
		int FPS;
	private:
		unsigned int projUniformLocation;
		unsigned int transUniformLocation;
		unsigned int viewUniformLocation;
		unsigned int colorUniformLocation;
	private:
		unsigned int shaderProgram;
	private:
		GLFWwindow* window;
	public:
		void EventStart();
		void EventUpdate(Hyko::Time ts);
	};
}