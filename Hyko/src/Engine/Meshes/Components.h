#pragma once

// GL / Maths
#include <glm/glm.hpp>

namespace Hyko {
	struct Triangle{
	public:
		static int count;
		int indx = 0;

		int8_t type;

		glm::vec2 m_position = { 0.0f, 0.0f };
		glm::vec2 m_scale	 = { 1.0f, 1.0f };
		glm::vec4 m_color	 = { 1.0f, 1.0f, 1.0f, 1.0f };

		float m_rotation = 0.0f;
	};

	struct TransformComponent {
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(glm::mat4 transform)
			: Transform(transform){}
	};

	struct SpriteComponent {
		glm::vec4 Color{ 1.0f, 0.0f, 1.0f, 1.0f };

		enum Type {
			Triangle, Rectangle, Circle
		};

		Type type;

		SpriteComponent() = default;
		SpriteComponent(glm::vec4 color)
			: Color(color) {}
	};

	struct CircleSpriteComponent {
		glm::vec4 Color{1.0f, 0.0f, 1.0f, 1.0f};
		float radius = 10.0f;
		int segmentsCount = 30;

		CircleSpriteComponent() = default;
		CircleSpriteComponent(glm::vec4 color)
			: Color(color) {}
	};

	struct IDComponent {
	private:
		static int IDCount;
	public:
		size_t ID = 0;

		IDComponent() {
			IDCount++;
			ID = IDCount - 1;
		}
		IDComponent(size_t id)
			: ID(id){}
	};
}