#pragma once

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// std
#include <vector>
#include <memory>

#include "GL/VO.h"
#include "Engine/Scene/Scene.h"

namespace Hyko {
	struct vertex {
		glm::vec3 position;
		glm::vec4 color;
	};

	class Entity{
	private:
		vertex m_vertex;
		std::shared_ptr<Hyko::Scene> m_scene;

		VO vo;
	private:
		static std::vector<float> triangleVertices;
		static std::vector<std::vector<vertex>> vert;
		std::vector<std::vector<vertex>> constVert;
		static std::vector<unsigned int> triangleIndices;
	private:
		void addTriangleVertexes(glm::vec3 position_one, glm::vec3 position_two, glm::vec4 color);
		void addTriangleIndiceses();
	public:
		Entity() = default;
		Entity(std::shared_ptr<Scene>& scene)
			: m_scene(scene) {}
		~Entity() = default;

		Hyko::Triangle& addToSceneTriangle();
		Hyko::Triangle& addToSceneTriangle(glm::vec2 pos, float rot, glm::vec2 scale, glm::vec4 color);
		Hyko::Triangle& addToSceneTriangle(float posX, float posY, float rot, float scaleX, float scaleY, float colorR, float colorG, float colorB, float colorA);

		void render(int8_t type);

		void ConverteToVertPos(int8_t type, glm::vec2 pos, glm::vec2 meshScale);
		glm::vec3 ConverteToObjectPos(std::vector<vertex> vertexes);

		void ConvertVertexToVertices(std::vector<std::vector<vertex>> vertexes);

		template<typename T>
		void setPosition(T comp, int8_t type, glm::vec2 newPos) {
			int indx = comp.indx;

			glm::mat4 pos = glm::scale(glm::mat4(1.0f), { comp.m_scale, 0.0f }) * glm::rotate(glm::mat4(1.0f), comp.m_rotation, { 0.0f, 0.0f, 1.0f }) * glm::translate(glm::mat4(1.0f), { newPos, 0.0f });

			if (type == HK_TRIANGLE) {
				vert[indx][0].position = pos * glm::vec4(vert[indx][0].position, 1.0f);
				vert[indx][1].position = pos * glm::vec4(vert[indx][1].position, 1.0f);
				vert[indx][2].position = pos * glm::vec4(vert[indx][2].position, 1.0f);

				triangleVertices.clear();
				ConvertVertexToVertices(vert);

				vo.deleteVO();
				vo.createVertexObjects(triangleVertices, 7, triangleIndices);
			}
		};
		void setPosition(int indx, int8_t type, glm::vec2 newPos);

		template<typename T>
		void setScale(T comp, int8_t type, glm::vec2 newScale) {
			int indx = comp.indx;

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), { newScale, 0.0f }) * glm::rotate(glm::mat4(1.0f), comp.m_rotation, { 0.0f, 0.0f, 1.0f }) * glm::translate(glm::mat4(1.0f), { comp.m_position, 0.0f });

			if (type == HK_TRIANGLE) {
				vert[indx][0].position = scale * glm::vec4(vert[indx][0].position, 1.0f);
				vert[indx][1].position = scale * glm::vec4(vert[indx][1].position, 1.0f);
				vert[indx][2].position = scale * glm::vec4(vert[indx][2].position, 1.0f);

				triangleVertices.clear();
				ConvertVertexToVertices(vert);

				vo.deleteVO();
				vo.createVertexObjects(triangleVertices, 7, triangleIndices);
			}
		};
		void setScale(int indx, int8_t type, glm::vec2 newScale);

		template<typename T>
		void setRot(T comp, int8_t type, float angle) {
			int indx = comp.indx;

			glm::mat4 rot = glm::translate(glm::mat4(1.0f), { comp.m_position, 0.0f }) * glm::scale(glm::mat4(1.0f), { comp.m_scale, 0.0f }) * glm::rotate(glm::mat4(1.0f), angle, { 0.0f, 0.0f, 1.0f });

			if (type == HK_TRIANGLE) {
				vert[indx][0].position = rot * glm::vec4(vert[indx][0].position, 1.0f);
				vert[indx][1].position = rot * glm::vec4(vert[indx][1].position, 1.0f);
				vert[indx][2].position = rot * glm::vec4(vert[indx][2].position, 1.0f);

				triangleVertices.clear();
				ConvertVertexToVertices(vert);

				vo.deleteVO();
				vo.createVertexObjects(triangleVertices, 7, triangleIndices);
			}
		};
		void setRot(int indx, int8_t type, float angle);

		template<typename T>
		void setColor(T comp, int8_t type, glm::vec4 color) {
			int indx = comp.indx;

			if (type == HK_TRIANGLE) {
				vert[indx][0].color = color;
				vert[indx][1].color = color;
				vert[indx][2].color = color;

				triangleVertices.clear();
				ConvertVertexToVertices(vert);

				vo.deleteVO();
				vo.createVertexObjects(triangleVertices, 7, triangleIndices);
			}
		};
		void setColor(int indx, int8_t type, glm::vec4 newColor);

		void EndDraw();

		////getters////////////////////////////////////////////////////////////////////

		glm::vec3 getVertPosX(int8_t type);
		glm::vec3 getVertPosY(int8_t type);
		glm::vec3 getVertPosZ(int8_t type);

		size_t getTriangleCount() { return vert.size(); };

		///////////////////////////////////////////////////////////////////////////////
	};
}