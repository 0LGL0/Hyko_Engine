#pragma once

// GL / Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <typeindex>
#include <algorithm>

namespace Hyko {
	struct GroupComponent;

	struct TransformComponent {
		glm::vec2 translate	   { 0.0f };
		glm::vec2 scale		   { 10.0f };
		float rotAngle		   = 0.0f;

		// Transform variables from the previous frame
		glm::vec2 lastTranslate = translate;
		glm::vec2 lastScale = scale;
		float lastRotAngle = rotAngle;

		/*bool isMoving  = false;
		bool isScaling = false;
		bool isRotated = false;*/

		TransformComponent() = default;
		TransformComponent(const glm::vec2 _translate, const glm::vec2 _scale, const float _rotAngle)
			: translate(_translate), scale(_scale), rotAngle(_rotAngle) {}

		void clone(TransformComponent& component) {
			component.translate = this->translate;
			component.scale		= this->scale;
			component.rotAngle  = this->rotAngle;
		}

		const glm::mat4 getTransform() const {
			return glm::translate(glm::mat4(1.0f), glm::vec3(translate, 0.0f))
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotAngle), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
		}

		void setTransform(glm::mat4 transform);

		const bool isMoving() const { return translate.x - lastTranslate.x != 0.0f || translate.y - lastTranslate.y != 0.0f; }
		const bool isScaling() const { return scale.x - lastScale.x != 0.0f || scale.y - lastScale.y != 0.0f; }
		const bool isRotated() const { return rotAngle - lastRotAngle != 0.0f; }
	private:
		std::string compName = "Transform component";
		friend class EComponentSettings;
	};

	struct RelativeTransformComponent {
		glm::vec2 translate{ 0.0f };
		glm::vec2 scale{ 0.0f };
		float rotAngle{ 0.0f };

		RelativeTransformComponent() = default;
		RelativeTransformComponent(const glm::vec2 _translate, const glm::vec2 _scale, const float _rotAngle)
			: translate(_translate), scale(_scale), rotAngle(_rotAngle) {}

		const glm::mat4 getRelativeTransform() const {
			return glm::translate(glm::mat4(1.0f), glm::vec3(translate, 0.0f))
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotAngle), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
		}

		void update(TransformComponent parentTransform, TransformComponent childTransform) {
			const auto parentInv = glm::inverse(parentTransform.getTransform());

			translate = glm::vec2(parentInv * glm::vec4(childTransform.translate, 0.0f, 1.0f));
			scale = glm::vec2(glm::vec4(childTransform.scale, 1.0f, 1.0f) / glm::vec4(childTransform.scale, 0.0f, 1.0f));
			rotAngle = glm::degrees(childTransform.rotAngle - parentTransform.rotAngle);
		}

		void clone(RelativeTransformComponent& component) {
			component.translate = this->translate;
			component.scale = this->scale;
			component.rotAngle = this->rotAngle;
		}
	};

	struct SpriteComponent {
		glm::vec4 Color{ 1.0f, 0.0f, 1.0f, 1.0f };
		int circleSegmentCount = 16;

		enum Type {
			Triangle, Rectangle, Circle, Entity
		};

		Type type;

		SpriteComponent() = default;
		SpriteComponent(const glm::vec4 color)
			: Color(color), type(Triangle) {}

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
		IDComponent(const size_t id)
			: ID(id){}

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
		TagComponent(const std::string tag)
			: Tag(tag){}

		void clone(TagComponent& component) {
			component.Tag = this->Tag;
		}

	private:
		std::string compName = "Tag component";
		friend class EComponentSettings;
	};

	struct GroupComponent {
		uint32_t parent = -1;
		bool isParent = false;
		bool isChild = false;
		std::vector<uint32_t> group;

		glm::vec2 translateOffset{ 0.0f }; // distance between parent and child entity
		glm::vec2 scaleOffset{ 0.0f }; // scale offset relative to parent and child entity
		float rotAngleOffset = 0.0f; // rotation angle offset relative to parent and child entity

		GroupComponent() = default;
		GroupComponent(const std::vector<uint32_t> _group)
			: group(group) {}

		void addEntityToGroup(const uint32_t entityID);
		void moveToMainBranch(const uint32_t entityID);

		void clone(GroupComponent& component) {
			component.group = this->group;
			component.parent = this->parent;
			component.isParent = this->isParent;
			component.isChild = this->isChild;
			component.translateOffset = this->translateOffset;
			component.scaleOffset = this->scaleOffset;
			component.rotAngleOffset = this->rotAngleOffset;
		}
	};

	// Return sprite type name
	std::string getSpriteTypeName(SpriteComponent::Type type);
}