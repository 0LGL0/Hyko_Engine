#pragma once

#include "../Engine/Core/Hyko.h"
#include "../Engine/UI/Editor/MainEditorUI/UI.h"
#include "../Meshes/Entity.h"
#include "../Engine/Projection/EditorProjection.h"
#include "../Engine/ImGui/ImGuiWindows.h"
#include "../Engine/Debug/Debug.h"
#include "../../window.h"
#include <imgui.h>
#include <glm/glm.hpp>

namespace Hyko {
	class EUpdates {
	private:
		EProjection EProj;
		Hyko::EUI MainEditoreUI;
	private:
		/*Triangle triangle;
		Triangle tr;*/

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
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

		glm::vec2 pos = glm::vec2(0.0f);
		glm::vec2 scale = {1.0f, 1.0f};
		glm::vec4 color= glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		float angle = 0.0f;

		int indxTiangle;
	private:
		unsigned int shaderProgram;
	private:
		GLFWwindow* window;
	public:
		void EventStart();
		void EventUpdate(Hyko::Time ts);
	};
}