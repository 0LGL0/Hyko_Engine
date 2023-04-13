#pragma once

#include "GL/Window/window.h"
#include "Engine/Buffers/OpenGL/Framebuffer.h"

// GL / Maths
#include <glm/glm.hpp>

// std
#include <memory>

namespace Hyko{
	class Camera {
	private:
		float m_left      = -100.0f;
		float m_right     =  100.0f;
		float m_top       =  100.0f;
		float m_bottom    = -100.0f;
		float m_zoomValue = 0.2f;

		int m_camSpeed = 40;

		glm::vec2 m_pos = glm::vec2(0.0f);

		glm::mat4 m_viewMat = glm::mat4(1.0f);
		glm::mat4 m_projMat = glm::mat4(1.0f);
	public:
		Camera(const float _left = -100.0f, const float _right = 100.0f, const float _top = 100.0f, const float _bottom = -100.0f)
			: m_left(_left), m_right(_right), m_top(_top), m_bottom(_bottom) {}

	public: // setters
		void setPos(const glm::vec2 newPos) { setPos(newPos.x, newPos.y); }
		void setPos(const float x, const float y) { m_pos = {x, y}; }
		void setCamSpeed(const int value) { m_camSpeed = value; };
	public: // getters
		const glm::vec2 getPos() const { return m_pos; }
		const glm::mat4 getViewMat() const { glm::inverse(m_viewMat); return m_viewMat; }
		const glm::mat4 getProjMat() const { return m_projMat; }

		const int getCamSpeed() const { return m_camSpeed; }
	public:
		void updateInput(const float dt);
		void updateView();
		void updateProjection(std::shared_ptr<FBO> fbo);
	};
}