#pragma once

// GL / Maths
#include <glm/glm.hpp>

namespace Hyko {
	struct OrthographicData {
		float m_left	= 0;
		float m_right	= 0;
		float m_bottom	= 0;
		float m_top		= 0;

		OrthographicData() = default;
		OrthographicData(float left ,float right, float bottom, float top)
			: m_left(left), m_right(right), m_bottom(bottom), m_top(top){}
	};

	struct PerspectiveData {
		float m_fovY	= 0;
		float m_aspect	= 0;
		float m_zNear	= 0;
		float m_zFar	= 0;

		PerspectiveData() = default;
		PerspectiveData(float fovY, float aspect, float zNear, float zFar)
			: m_fovY(fovY), m_aspect(aspect), m_zNear(zNear), m_zFar(zFar){}
	};

	enum projType {
		Orthographic, Perspective
	};

	class ECamera {
	private:
		OrthographicData m_orthoData;
		PerspectiveData  m_perspData;
		projType m_type;
	private:
		glm::mat4 m_projectionMat = glm::mat4(1.0f);
		glm::mat4 m_viewMat		  = glm::mat4(1.0f);

		glm::vec2 m_position = glm::vec2(0.0f);
	public:
		ECamera() = default;
		ECamera(Hyko::OrthographicData data, glm::vec2 position = glm::vec2(0.0f));
		ECamera(Hyko::PerspectiveData data, glm::vec2 position = glm::vec2(0.0f));
		~ECamera() = default;

		void initProjection();
		void updateInput(float dt, float camSpeed);

		glm::mat4 updateView();
		glm::mat4 updateProjection();

		void swapProjection(Hyko::projType type);
	public: // setters
		void setPosition(glm::vec2 newPos);
		void setPosition(float x, float y);

		void setData(Hyko::OrthographicData data);
		void setData(Hyko::PerspectiveData data);
	public: // getters
		glm::mat4 getProjectionMat() { return m_projectionMat; }
		glm::mat4 getViewMat() { return m_viewMat; }

		glm::vec2 getPosition() { return m_position; }
	};
}