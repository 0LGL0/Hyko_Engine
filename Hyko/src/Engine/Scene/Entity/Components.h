#pragma once

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <typeindex>

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
		//glm::mat4 Transform{ 1.0f };

		glm::vec2 translate{0.0f};
		glm::vec2 scale{10.0f};
		float rotAngle = 0.0f;

		TransformComponent() = default;
		TransformComponent(const glm::vec2 _translate, const glm::vec2 _scale, const float _rotAngle)
			: translate(_translate), scale(_scale), rotAngle(_rotAngle) {}
		TransformComponent(const TransformComponent& copy)
			: translate(copy.translate), scale(copy.scale), rotAngle(copy.rotAngle) {}
		TransformComponent(TransformComponent&& other) noexcept
		: translate(0), scale(0), rotAngle(0) {
			translate = other.translate;
			scale = other.scale;
			rotAngle = other.rotAngle;

			other.translate = glm::vec2(0);
			other.scale		= glm::vec2(0);
			other.rotAngle	= 0.0f;
		}

		TransformComponent& operator=(const TransformComponent& copy) {
			translate = copy.translate;
			scale	  = copy.scale;
			rotAngle  = copy.rotAngle;

			return *this;
		}

		TransformComponent& operator=(TransformComponent&& other) noexcept {
			if (this != &other) {
				translate = other.translate;
				scale = other.scale;
				rotAngle = other.rotAngle;

				other.translate = glm::vec2(0);
				other.scale = glm::vec2(0);
				other.rotAngle = 0.0f;
			}

			return *this;
		}

		void clone(TransformComponent& component) {
			component.translate = this->translate;
			component.scale		= this->scale;
			component.rotAngle  = this->rotAngle;
		}

		glm::mat4 getTransform() {
			return glm::translate(glm::mat4(1.0f), glm::vec3(translate, 0.0f))
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotAngle), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
		}

	private:
		std::string compName = "Transform component";
		friend class EComponentSettings;
	};

	struct SpriteComponent {
		glm::vec4 Color{ 1.0f, 0.0f, 1.0f, 1.0f };
		int circleSegmentCount = 16;

		enum Type {
			Triangle, Rectangle, Circle, Entity
		};

		Type type;

		SpriteComponent() = default;
		SpriteComponent(glm::vec4 color)
			: Color(color), type(Triangle) {}
		SpriteComponent(const SpriteComponent& copy)
			: Color(copy.Color), circleSegmentCount(copy.circleSegmentCount), type(copy.type){}

		SpriteComponent(SpriteComponent&& other) noexcept
			: Color(0), circleSegmentCount(0) {
			Color			   = other.Color;
			circleSegmentCount = other.circleSegmentCount;
			type			   = other.type;

			other.Color				 = glm::vec4(0);
			other.circleSegmentCount = 0;
			other.type				 = Entity;
		}

		SpriteComponent& operator=(const SpriteComponent& copy) {
			Color			   = copy.Color;
			circleSegmentCount = copy.circleSegmentCount;
			type			   = copy.type;

			return *this;
		}

		SpriteComponent& operator=(SpriteComponent& other) {
			if (this != &other) {
				Color			   = other.Color;
				circleSegmentCount = other.circleSegmentCount;
				type			   = other.type;

				other.Color = glm::vec4(0);
				other.circleSegmentCount = 0;
				other.type = Entity;
			}

			return *this;
		}

		void clone(SpriteComponent& component) {
			component.Color				 = this->Color;
			component.circleSegmentCount = this->circleSegmentCount;
			component.type				 = this->type;
		}

	private:
		std::string compName = "Sprite component";
		friend class EComponentSettings;
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
		IDComponent(const IDComponent& copy)
			: ID(copy.ID){}

		IDComponent(IDComponent&& other) noexcept
			: ID(0) {
			ID = other.ID;

			other.ID = 0;
		}

		IDComponent& operator=(const IDComponent& copy) {
			ID = copy.ID;

			return *this;
		}

		IDComponent& operator=(IDComponent&& other) noexcept {
			if (this != &other) {
				ID = other.ID;

				other.ID = 0;
			}

			return *this;
		}

		void clone(IDComponent& component) {
			component.ID = this->ID;
		}

	private:
		std::string compName = "ID component";
		friend class EComponentSettings;
	};

	struct TagComponent {
		std::string Tag;

		TagComponent() = default;
		TagComponent(std::string tag)
			: Tag(tag){}
		TagComponent(const TagComponent& copy)
			: Tag(copy.Tag){}

		TagComponent(TagComponent&& other) noexcept
			: Tag("") {
			Tag = other.Tag;

			other.Tag = "";
		}

		TagComponent& operator=(const TagComponent& copy) {
			Tag = copy.Tag;

			return *this;
		}

		TagComponent& operator=(TagComponent&& other) noexcept {
			if (this != &other) {
				Tag = other.Tag;

				other.Tag = "";
			}

			return *this;
		}

		void clone(TagComponent& component) {
			component.Tag = this->Tag;
		}

	private:
		std::string compName = "Tag component";
		friend class EComponentSettings;
	};

	// Return sprite type name
	std::string getSpriteTypeName(SpriteComponent::Type type);
}