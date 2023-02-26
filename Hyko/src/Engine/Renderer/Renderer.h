#pragma once

#include "RendererTools.h"

// shader load and compile
#include "Engine/System/FileSystem/shader.h"
#include "Engine/Scene/Camera/EditorCamera.h"

#include "Engine/Scene/Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace Hyko {
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	struct RendererData {
		RendererTools m_rTools;
		
		std::shared_ptr<Hyko::Scene> m_scene;

		glm::mat4 projection;
		glm::mat4 view;

		RendererData() = default;
		RendererData(std::shared_ptr<Hyko::Scene>& scene)
			: m_scene(scene) {}

		unsigned int circleProgram;
		unsigned int basicProgram;

		const glm::vec3 triangleVertexPos[3]{
			{-0.5f, -0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f},
			{ 0.0f,  0.5f, 0.0f}
		};

		const glm::vec3 rectangleVertexPos[4]{
			{-0.5f, -0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f},
			{ 0.5f,  0.5f, 0.0f},
			{-0.5f,  0.5f, 0.0f}
		};

		std::vector<float> vertices;
		std::vector<unsigned int> index;

		std::vector<float> circleVertices;
		std::vector<unsigned int> circleIndices;

		short int trianglesCount;
		short int rectanglesCount;
		short int circlesCount;
	};

	class Renderer{
	private:
		static void addTriangleIndiceses();
		static void addRectangleIndiceses();
		static void addCircleIndiceses(const int segmentsCount);
	public:
		Renderer() = default;

		static void createTriangle();
		static void createTriangle(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec4 color);
		static void createTriangle(glm::mat4 transform, glm::vec4 color);

		static void createRectangle();
		static void createRectangle(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec4 color);
		static void createRectangle(glm::mat4 transform, glm::vec4 color);

		static void createCircle();
		static void createCircle(glm::vec2 pos, glm::vec2 scale, int segmentsCount, float angle, glm::vec4 color);
		static void createCircle(glm::mat4 transform, glm::vec4 color, int segmentsCount);

		static void Init();

		static void Update();

		static void BeginScene();
		static void EndScene();

		static void render();
	};
}