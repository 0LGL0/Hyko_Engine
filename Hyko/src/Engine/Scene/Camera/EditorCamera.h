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
		static OrthographicData m_orthoData;
		static PerspectiveData  m_perspData;
		static projType m_type;
	private:
		static glm::mat4 m_projectionMat;
		static glm::mat4 m_viewMat;
		static glm::vec2 m_position;

		static int zoomValue;
	public:
		ECamera() = default;
		ECamera(Hyko::OrthographicData data, glm::vec2 position = glm::vec2(0.0f));
		ECamera(Hyko::PerspectiveData data, glm::vec2 position = glm::vec2(0.0f));
		~ECamera();

		static void initProjection();
		static void updateInput(float dt, float camSpeed);

		static glm::mat4 updateView();
		static glm::mat4 updateProjection();

		static void swapProjection(Hyko::projType type);

		static void Resize(float width, float height);
	public: // setters
		static void setPosition(glm::vec2 newPos);
		static void setPosition(float x, float y);

		static void setData(Hyko::OrthographicData data);
		static void setData(Hyko::PerspectiveData data);
	public: // getters
		static glm::mat4 getProjectionMat() { return m_projectionMat; }
		static glm::mat4 getViewMat() { return m_viewMat; }

		static glm::vec2 getPosition() { return m_position; }
	};
}